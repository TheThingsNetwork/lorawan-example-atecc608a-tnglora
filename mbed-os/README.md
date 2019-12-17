# ATECC608A-TNGLORA LoRaWAN example application for Arm Mbed OS 

This is an example application to show the use of a pre-provisioned secure element (ATECC608A-TNGLORA) in LoRaWAN OTAA join flow.

The MBED OS LoRaWAN stack is modified based on this [branch](https://github.com/hasnainvirk/mbed-os/tree/ATECC608_PoC) to support the use of an external pre-provisioned crypto chip in the LoRaWAN. This example is an extension to the work done [here](https://github.com/ARMmbed/mbed-os-example-lorawan-atecc608a) and [here](https://github.com/MicrochipTech/cryptoauthlib/wiki/TTN-Getting-Started#software-packages-and-code-example) to provide an up to date example of using the latest crypto module [ATECC608A-TNGLORA](https://www.microchip.com/wwwproducts/en/ATECC608A-TNGLORA) in a LoRaWAN application.

## Requirements

You'll need the following hardware:

- Any [Mbed-enabled development board](https://os.mbed.com/platforms/).
- An [ATECC608A-TNGLORA](https://www.microchip.com/wwwproducts/en/ATECC608A-TNGLORA) in UDFN or SOIC package.
- An interfacing board such as [CryptoAuthentication™ UDFN Socket Kit](https://www.microchip.com/DevelopmentTools/ProductDetails/AT88CKSCKTUDFN-XPRO) extension board (see [secure element interfacing options](../HW/interfacing.md) for more information).
- An SX1272 or SX1276 LoRa radio (only in case your development board has no LoRa radio), such as the [SX1272MB2xAS](https://os.mbed.com/components/SX1272MB2xAS/) or [SX1276MB1xAS](https://os.mbed.com/components/SX1276MB1xAS/) shield.

## Configuration

Open the configuration file `mbed_app.json`. This file contains the user specific configuration your application and the Mbed OS LoRaWAN stack needs.

Set `lora.version`. The values supported are:

* `0` - LoRaWAN 1.0.2
* `1` - LoRaWAN 1.0.3
* `10` - LoRaWAN 1.1.1

Set the region:

```json
"lora.phy": "EU868"
```

Valid values are `AS923`, `AU915`, `CN470`, `CN779`, `EU433`, `IN865`, `KR920` and `US915`.

When deploying in a duty-cycle region (i.e.`EU868`), enable duty-cycle:

```json
"lora.duty-cycle-on": true,
```

Connect the secure element to your development board using the [interfacing](../HW/interfacing.md) method of your choice.

Set the pin names accordingly:

```json
"cryptoauthlib.i2c_sda": "PXXX",
"cryptoauthlib.i2c_scl": "PXXX"
```

Connect the LoRa radio shield to the SPI bus.

Set the LoRa Radio and pin names accordingly:

```json
"lora-radio":          "SX1276",
"lora-spi-mosi":       "PXXX",
"lora-spi-miso":       "PXXX",
"lora-spi-sclk":       "PXXX",
"lora-cs":             "PXXX",
"lora-reset":          "PXXX",
"lora-dio0":           "PXXX",
"lora-dio1":           "PXXX",
"lora-dio2":           "PXXX",
"lora-dio3":           "PXXX",
"lora-dio4":           "PXXX",
"lora-dio5":           "PXXX",
"lora-rf-switch-ctl1": "PXXX",
"lora-rf-switch-ctl2": "PXXX",
"lora-txctl":          "NC",
"lora-rxctl":          "NC",
"lora-ant-switch":     "NC",
"lora-pwr-amp-ctl":    "NC",
"lora-tcxo":           "PXXX"
```
 

## Module support

The modules/boards below where tested and the application is proving functional with minimal configuration.

- `SAMR34_XPLAINED_PRO`, see [Using SAMR34 with ATECC608A-TNGLORA](../HW/samr34_xplained.md).
- `SAML21J18A` (SAML21 Xplained Pro),see [Using SAML21 with ATECC608A-TNGLORA](../HW/saml21_xplained.md).

## Compiling the application

Use [Mbed CLI](https://os.mbed.com/docs/mbed-os/v5.14/tools/developing-mbed-cli.html) to deploy and compile the binary:

First, deploy the dependencies:

```sh
$ mbed deploy
```

Then, compile the application:

```sh
$ mbed compile -m YOUR_TARGET -t GCC_ARM
```

## Running the application

You will need to flash the application binary found in `BUILD/YOUR_TARGET/GCC_ARM/mbed-os.bin` to your Mbed enabled target hardware.

Some boards appear as external USB devices, a simple drag and drop of the binary is enough.
Other boards will require flashing the binary using a debugger, this is shown extensively per board in the getting started section.

Attach a serial console emulator of your choice (for example, PuTTY, Minicom or Serial) to your USB device/board. Set the baud-rate to 115200 bit/s, and reset your board by recycling power or pressing the reset button.

You should see an output similar to this:

```
Mbed OS LoRaWAN example for ATECC608A-TNGLoRa 
         SE Serial Number:          01 23 5f cd a1 cc 07 2e 27 
         SE Device EUI:             00 04 a3 10 00 1a a6 98 
         SE Application/Join EUI:   70 b3 d5 7e d0 00 00 00 
[DBG ][LSTK]: Initializing MAC layer
Mbed LoRaWANStack initialized 
Adaptive data  rate (ADR) - Enabled 
[DBG ][LSTK]: Initiating OTAA
[DBG ][LSTK]: Sending Join Request ...
[DBG ][LMAC]: Frame prepared to send at port 0
[DBG ][LMAC]: TX: Channel=2, TX DR=5, RX1 DR=5
Connection - In Progress ...
```

## Optional: Enable tracing

To enable Mbed trace, set the following field in `mbed_app.json`:

```json
"target_overrides": {
  "*": {
    "mbed-trace.enable": true
  }
}
```

The trace is disabled by default to save RAM and reduce main stack usage.

>Please note that some targets with small RAM size, mbed traces cannot be enabled without increasing the default `"main_stack_size": 1024`
