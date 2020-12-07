# LoRaMac-node ATECC608A-TNGLoRa

[LoRaMac-node](https://github.com/Lora-net/LoRaMac-node) is a bare-metal reference implementation of the LoRaWAN stack, it provides various example applications to multiple development boards.

The [LoRaMac-node](https://github.com/Lora-net/LoRaMac-node) `develop` branch supports ATECC608A-TNGLORA as a HW secure element.

This support means that (theoretically with the correct I2C config) all the devices/boards supported by LoRaMac-node now support using ATECC608A-TNGLORA as an external HW secure element.

## Supported Targets

The ATECC608A-TNGLORA communicates via the I2C bus, this means with a proper I2C initialization any microcontroller can communicate with the ATECC608A-TNGLORA.

### Microchip SAMR34 Support

In the `develop` branch we add  I2C support for the [SAMR34 Xplained Pro Evaluation Kit](https://www.microchip.com/DevelopmentTools/ProductDetails/dm320111) board.

> Make sure to set `BOARD` to `SAMR34` in the CMAKE building system.

### Other Targets

Since LoRaMac-node is a bare-metal platform, you can adapt any [LoRaMac-node supported platform](https://github.com/Lora-net/LoRaMac-node/#supported-platforms) to use new or existing I2C pins and communicate with the ATECC608A-TNGLORA similar to the SAMR34.

## Supported Applications

All applications are supported, as by default, all applications join the network via OTAA (`OVER_THE_AIR_ACTIVATION` flag `Commissioning.h`)

## Getting Started

1. Get familiar with [LoRaMac-node repository](https://github.com/TheThingsNetwork/LoRaMac-node/#introduction)
2. Follow the detailed [Usage](https://github.com/TheThingsNetwork/LoRaMac-node/#usage) instructions
3. To test with SAMR34 target, checkout the [LoRaMac-node](https://github.com/Lora-net/LoRaMac-node) `develop` branch.
	- `$ git clone --branch develop --recurse-submodules https://github.com/Lora-net/LoRaMac-node.git`
4. Set CMAKE building system flags (`cmake.configureSettings`) as seen below.
	- `APPLICATION`:`LoRaMac`
	- `SUB_PROJECT`:`periodic-uplink-lpp`
	- `BOARD`:`SAMR34`
	- `SECURE_ELEMENT`:`ATECC608A_TNGLORA_SE`
5. Build and flash the application to your SAMR34 Xplained Pro Evaluation Kit.
