# Examples of LoRaWAN ATECC608A-TNGLORA

Incorporating secure elements such as [ATECC608A-TNGLORA](https://www.microchip.com/wwwproducts/en/ATECC608A-TNGLORA) in the design and production of LoRaWAN end-devices is [considered](https://www.linkedin.com/pulse/securing-lorawan-secure-elements-johan-stokking/) a best practice.

In this repository we provide practical tutorials and examples of using the [ATECC608A-TNGLoRa](https://www.microchip.com/wwwproducts/en/ATECC608A-TNGLORA) with various LoRaWAN stacks and devices.

## Requirements

- Any LoRaWAN network with a join server that supports ATECC608A-TNGLORA

> [The Things Enterprise Stack](https://enterprise.thethingsstack.io/) already supports claiming ATECC608A-TNGLORA devices. Make sure you can follow this [guide](https://enterprise.thethingsstack.io/v3.5.3/guides/claim-atecc608a/)

- Any microcontroller with a LoRa transceiver and I2C support 

> See [HW](./HW) for more details about interfacing the secure element and example boards/connections)

- A UDFN or SOIC packaged [ATECC608A-TNGLORA](https://www.microchip.com/wwwproducts/en/ATECC608A-TNGLORA)

## Support
LoRaWAN communication is end-to-end encrypted, therefore the use of an external secure elements requires a deep integration within the end-device LoRaWAN stack.

In this repository we integrate the [ATECC608A-TNGLORA](https://www.microchip.com/wwwproducts/en/ATECC608A-TNGLORA) with popular open-source LoRaWAN stacks such as:

- [Mbed OS](https://github.com/ARMmbed/mbed-os)
- [LoRaMac-node](https://github.com/Lora-net/LoRaMac-node)

It is also worth mentioning that [ATECC608A-TNGLORA](https://www.microchip.com/wwwproducts/en/ATECC608A-TNGLORA) is integrated with Microchip LoRaWAN stack as seen [here](https://github.com/MicrochipTech/cryptoauthlib/wiki/TTN-Getting-Started).

> Currently, all the examples allow for using the ATECC608A-TNGLORA in encryption and decryption of the payloads and OTAA joins with LoRaWAN 1.0.x with
planned future support of multicast and LoRaWAN 1.1

## Getting started

Instructions are provided per LoRaWAN stack/platform.

- [Mbed OS](./mbed-os/README.md)
- LoRaMac-node
