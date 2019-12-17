/** Copyright © 2020 The Things Industries B.V.
*
* Licensed under the Apache License, Version 2.0 (the "License");
* you may not use this file except in compliance with the License.
* You may obtain a copy of the License at
*
*     http://www.apache.org/licenses/LICENSE-2.0
*
* Unless required by applicable law or agreed to in writing, software
* distributed under the License is distributed on an "AS IS" BASIS,
* WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
* See the License for the specific language governing permissions and
* limitations under the License.
*/

#include "mbed.h"
#include "mbed_events.h"
#include "mbed_trace.h"
#include "lora_radio_helper.h"
#include "LoRaWANInterface.h"
#include "CayenneLPP.h"

// For ATECC608 Secure element
#include "cryptoauthlib.h"
#include "atca_devtypes.h"
#include "tnglora_read_helper.h"

static ATCAIfaceCfg atecc608_i2c_config;

#define TX_INTERVAL 10000

static EventQueue ev_queue;
static void lora_event_handler(lorawan_event_t event);
static lorawan_app_callbacks_t callbacks;

static LoRaWANInterface lorawan(radio);

static void print_buffer(const char *message, uint8_t *buffer, size_t buffer_size)
{
    printf(message);
    for (size_t ix = 0; ix < buffer_size; ix++)
    {
        printf("%02x ", buffer[ix]);
    }
    printf("\r\n");
}

int main(void)
{
    mbed_trace_init();
    printf("\r\n Mbed OS LoRaWAN example for ATECC608A-TNGLoRa \r\n");
    // Setup secure element
    atecc608_i2c_config.iface_type = ATCA_I2C_IFACE;
    atecc608_i2c_config.atcai2c.baud = 100000;
    atecc608_i2c_config.atcai2c.bus = 2;
    atecc608_i2c_config.atcai2c.slave_address = 0xb2;
    atecc608_i2c_config.devtype = ATECC608A;
    atecc608_i2c_config.rx_retries = 20;
    atecc608_i2c_config.wake_delay = 1500;
    atcab_init(&atecc608_i2c_config);

    uint8_t secure_element_serialnum[ATCA_SERIAL_NUM_SIZE];
    uint8_t secure_element_devEUI[DEV_EUI_SIZE_BYTE];
    uint8_t secure_element_joinEUI[JOIN_EUI_SIZE_BYTE];

    ATCA_STATUS read_status = atcab_read_serial_number(secure_element_serialnum);
    if (read_status != ATCA_SUCCESS)
    {
        printf(" Failed to read ATECC608A serial number (%d) \r\n", read_status);
        return 1;
    }

    read_status = atcab_read_devEUI(secure_element_devEUI);
    if (read_status != ATCA_SUCCESS)
    {
        printf(" Failed to read ATECC608A devEUI (%d) \r\n", read_status);
        return 1;
    }

    read_status = atcab_read_joinEUI(secure_element_joinEUI);
    if (read_status != ATCA_SUCCESS)
    {
        printf(" Failed to read ATECC608A joinEUI (%d) \r\n", read_status);
        return 1;
    }

    print_buffer("\t SE Serial Number:          ", secure_element_serialnum, ATCA_SERIAL_NUM_SIZE);
    print_buffer("\t SE Device EUI:             ", secure_element_devEUI, DEV_EUI_SIZE_BYTE);
    print_buffer("\t SE Application/Join EUI:   ", secure_element_joinEUI, JOIN_EUI_SIZE_BYTE);

    lorawan_status_t retcode;

    // Initialize LoRaWAN stack
    if (lorawan.initialize(&ev_queue) != LORAWAN_STATUS_OK)
    {
        printf("LoRa initialization failed! \r\n");
        return -1;
    }

    printf("Mbed LoRaWANStack initialized \r\n");

    // prepare application callbacks
    callbacks.events = mbed::callback(lora_event_handler);
    lorawan.add_app_callbacks(&callbacks);

    // Set number of retries in case of CONFIRMED messages
    if (lorawan.set_confirmed_msg_retries(3) != LORAWAN_STATUS_OK)
    {
        printf("set_confirmed_msg_retries failed! \r\n\r\n");
        return -1;
    }

    // Enable adaptive data rate
    if (lorawan.enable_adaptive_datarate() != LORAWAN_STATUS_OK)
    {
        printf("enable_adaptive_datarate failed! \r\n");
        return -1;
    }

    printf("Adaptive data  rate (ADR) - Enabled \r\n");

    lorawan_connect_t connect_params;
    connect_params.connect_type = LORAWAN_CONNECTION_OTAA;

    connect_params.connection_u.otaa.dev_eui = secure_element_devEUI;
    connect_params.connection_u.otaa.app_eui = secure_element_joinEUI;
    connect_params.connection_u.otaa.app_key = (uint8_t *)MBED_CONF_LORA_APPLICATION_KEY; // Will use secure element root keys
    connect_params.connection_u.otaa.nwk_key = (uint8_t *)MBED_CONF_LORA_NETWORK_KEY;
    connect_params.connection_u.otaa.nb_trials = 10;

    retcode = lorawan.connect(connect_params);

    if (retcode == LORAWAN_STATUS_OK || retcode == LORAWAN_STATUS_CONNECT_IN_PROGRESS)
    {
        printf("Connection - In Progress ...\r\n");
    }
    else
    {
        printf("Connection error, code = %d \r\n", retcode);
        return -1;
    }

    // make your event queue dispatching events forever
    ev_queue.dispatch_forever();
}

/**
 * Sends a message to the Network Server
 */
static void send_message()
{

    float temperature = static_cast<float>(rand()) / static_cast<float>(RAND_MAX / 50) + 10.0f;

    printf("Temperature: %f\n", temperature);

    CayenneLPP payload(50);
    payload.addTemperature(1, temperature);

    int16_t retcode = lorawan.send(15, payload.getBuffer(), payload.getSize(), MSG_UNCONFIRMED_FLAG);

    if (retcode < 0)
    {
        retcode == LORAWAN_STATUS_WOULD_BLOCK ? printf("send - Duty cycle violation\r\n")
                                              : printf("send() - Error code %d \r\n", retcode);

        if (retcode == LORAWAN_STATUS_WOULD_BLOCK)
        {
            //retry in 3 seconds
            ev_queue.call_in(3000, send_message);
        }
        else
        {
            ev_queue.call_in(TX_INTERVAL, send_message);
        }
        return;
    }

    ev_queue.call_in(TX_INTERVAL, send_message);

    printf("%d bytes scheduled for transmission \r\n", retcode);
}

/**
 * Receive a message from the Network Server
 */
static void receive_message()
{
    uint8_t rx_buffer[50] = {0};
    uint8_t port;
    int flags;
    int16_t retcode = lorawan.receive(rx_buffer, sizeof(rx_buffer), port, flags);

    if (retcode < 0)
    {
        printf("receive() - Error code %d \r\n", retcode);
        return;
    }

    printf("RX Data on port %u (%d bytes): ", port, retcode);
    for (uint8_t i = 0; i < retcode; i++)
    {
        printf("%02x ", rx_buffer[i]);
    }
    printf("\r\n");
}

/**
 * Event handler
 */
static void lora_event_handler(lorawan_event_t event)
{
    switch (event)
    {
    case CONNECTED:
        printf("Connection - Successful \r\n");
        ev_queue.call_in(1000, send_message);
        break;
    case DISCONNECTED:
        ev_queue.break_dispatch();
        printf("Disconnected Successfully \r\n");
        break;
    case TX_DONE:
        printf("Message Sent to Network Server \r\n");
        break;
    case TX_TIMEOUT:
    case TX_ERROR:
    case TX_CRYPTO_ERROR:
    case TX_SCHEDULING_ERROR:
        printf("Transmission Error - EventCode = %d \r\n", event);
        break;
    case RX_DONE:
        printf("Received message from Network Server \r\n");
        receive_message();
        break;
    case RX_TIMEOUT:
    case RX_ERROR:
        printf("Error in reception - Code = %d \r\n", event);
        break;
    case JOIN_FAILURE:
        printf("OTAA Failed - Check Keys \r\n");
        break;
    case UPLINK_REQUIRED:
        printf("Uplink required by NS \r\n");
        send_message();
        break;
    default:
        MBED_ASSERT("Unknown Event");
    }
}
