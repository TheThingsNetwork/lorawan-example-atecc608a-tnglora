# Examples of LoRaWAN ATECC608A-TNGLORA

Incorporating secure elements such as [ATECC608A-TNGLORA](https://www.microchip.com/wwwproducts/en/ATECC608A-TNGLORA) in the design and production of LoRaWAN end-devices is [considered](https://www.linkedin.com/pulse/securing-lorawan-secure-elements-johan-stokking/) a best practice.

In this repository we provide practical tutorials and examples of using the [ATECC608A-TNGLORA](https://www.microchip.com/wwwproducts/en/ATECC608A-TNGLORA) with various LoRaWAN stacks and devices.

## Requirements

- Any LoRaWAN Network Server that supports the LoRaWAN Backend Interfaces and is configured to use The Things Industries Join Server

> [The Things Industries](https://www.thethingsindustries.com/technology) pre-configured cloud hosted already supports claiming ATECC608A-TNGLORA devices. Make sure you can follow this [guide](https://enterprise.thethingsstack.io/v3.5.3/guides/claim-atecc608a/)

- Any microcontroller with a LoRa transceiver and I2C support 

> See [HW](./HW) for more details about interfacing the secure element and example boards/connections

- A UDFN or SOIC packaged [ATECC608A-TNGLORA](https://www.microchip.com/wwwproducts/en/ATECC608A-TNGLORA)

## Support
LoRaWAN communication is end-to-end encrypted, therefore the use of an external secure elements requires a deep integration within the end-device LoRaWAN stack.

In this repository we integrate the [ATECC608A-TNGLORA](https://www.microchip.com/wwwproducts/en/ATECC608A-TNGLORA) with popular open-source LoRaWAN stacks such as:

- [Mbed OS](https://github.com/ARMmbed/mbed-os)
- [LoRaMac-node](https://github.com/Lora-net/LoRaMac-node)

It is also worth mentioning that [ATECC608A-TNGLORA](https://www.microchip.com/wwwproducts/en/ATECC608A-TNGLORA) is integrated with Microchip LoRaWAN stack as seen [here](https://github.com/MicrochipTech/cryptoauthlib/wiki/TTN-Getting-Started).

> Currently, all the examples allow for using the ATECC608A-TNGLORA in encryption and decryption of the payloads and OTAA joins with LoRaWAN 1.0.x with planned future support of multicast and LoRaWAN 1.1

## Getting started
We support multiple platforms, boards and device configurations.

For experienced Embedded/LoRaWAN users we recommend diving in with your preferred microcontroller/platform as ATECC608A-TNGLORA can be interfaced to any microcontroller/development board and this repository can act as a reference point for new integrations (bare-metal or OS based). 

For users looking for the fastest and simplist way to experience ATECC608A-TNGLORA, you can follow the steps below:

1. Get a [ATECC608A-TNGLORA](https://www.microchip.com/wwwproducts/en/ATECC608A-TNGLORA) in UDFN package, see [interfacing](./HW/interfacing.md) for more details.

2. Get UDFN click board from [here](https://www.microchip.com/DevelopmentTools/ProductDetails/AT88CKSCKTUDFN-XPRO) or [here](https://www.mikroe.com/secure-udfn-click)

3. Get one of the boards
	- [SAMR34 Xplained Pro Evaluation Kit](https://www.microchip.com/DevelopmentTools/ProductDetails/dm320111) (Examples with Mbed OS and LoRaMac-node)
 	- [MultiTech xDot® Micro Developer Kit](https://www.multitech.com/brands/micro-xdot-devkit) (Examples with Mbed OS)

4. Place the ATECC608A-TNGLORA inside the UDFN click board as seen [here](./HW/interfacing.md#how-to-use)

5. Connect your UDFN click board to your board
	- [SAMR34 Xplained Pro Evaluation Kit](./HW/samr34_xplained.md)
	- [MultiTech xDot® Micro Developer Kit](./HW/xdot.md)
 
6. Choose your preferred platform and follow the SW platform setup guide
	- [Mbed OS](./mbed-os/README.md)
	- LoRaMac-node
