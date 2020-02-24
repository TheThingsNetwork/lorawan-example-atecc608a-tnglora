#LoRaMac-node ATECC608A-TNGLoRa

LoRaMac-node is a bare-metal reference implementation of the LoRaWAN stack, it provides various example applications to multiple development boards.

In this [fork](https://github.com/TheThingsNetwork/LoRaMac-node/) we add support for ATECC608A-TNGLORA as a HW secure element.

This addition means that (theoretically) all the devices/boards supported by LoRaMac-node now support using ATECC608A-TNGLORA as an external HW secure element.

## Supported Targets

The ATECC608A-TNGLORA communicates via the I2C bus, this means with a proper I2C initialization any microcontroller can communicate with the ATECC608A-TNGLORA.

### Microchip SAMR34 Support

In this [branch](https://github.com/TheThingsNetwork/LoRaMac-node/tree/feature/SAMR34%2BATECC608A) we add  I2C support for the [SAMR34 Xplained Pro Evaluation Kit](https://www.microchip.com/DevelopmentTools/ProductDetails/dm320111) board based on the existing SAML21 support.

> Make sure to set `BOARD` to `SAMR34` in the CMAKE building system.

### Other Targets

Since LoRaMac-node is a bare-metal platform, you can adapt any [LoRaMac-node supported platform](https://github.com/TheThingsNetwork/LoRaMac-node/#supported-platforms) to use new or existing I2C pins and communicate with the ATECC608A-TNGLORA similar to the SAMR34.

## Supported Applications

All applications allow for joining over OTAA via `OVER_THE_AIR_ACTIVATION` flag in each application `Commissioning.h`.

## Getting Started

1. Get familiar with [LoRaMac-node repository](https://github.com/TheThingsNetwork/LoRaMac-node/#introduction)
2. Follow the detailed [Usage](https://github.com/TheThingsNetwork/LoRaMac-node/#usage) instructions
3. To test with SAMR34 target, checkout `feature/SAMR34+ATECC608A`[branch](https://github.com/TheThingsNetwork/LoRaMac-node/tree/feature/SAMR34%2BATECC608A)

4. Set CMAKE building system flags (`cmake.configureSettings`) as seen below.
	- `APPLICATION`:`LoRaMac`
	- `SUB_PROJECT`:`classA`	
	- `BOARD`:`SAMR34`
5. Build and flash the application to your SAMR34 Xplained Pro Evaluation Kit.
