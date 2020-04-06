# Hardware

[ATECC608A-TNGLORA](https://www.microchip.com/wwwproducts/en/ATECC608A-TNGLORA) communicates over the standard I2C bus, this makes it simple to integrate with old and new HW.

Any microcontroller/development board with I2C capabilities can easily interface with the secure element.

## Interfacing
You can order the [ATECC608A-TNGLORA](https://www.microchip.com/wwwproducts/en/ATECC608A-TNGLORA) in either UDFN or SOIC packages.

In [interfacing](interfacing.md), we explore how to easily connect to either IC package.

## Connections
We provide connection and application flashing instructions needed for the various supported boards.

These connections are tested and the SW is pre-configured to use the correlated I2C/UART/SPI pins shown in the connection guide.

> Please note that we show example of usage but you can have different connections depending on your choice of HW.

All the supported development boards have easy to use SW examples that make it fast to prototype using ATECC608A-TNGLORA.

**Currently supported development boards and platforms:**

| Development board                                            | Mbed OS   | LoRaMac-Node   |
| ------------------------------------------------------------ | ------------------ | ------------------ |
| [SAMR34 Xplained Pro Evaluation Kit](samr34_xplained.md)     | :heavy_check_mark: | :heavy_check_mark: |
| [MultiTech xDot® Micro Developer Kit](xdot.md)               | :heavy_check_mark: |                    |
| [SAM L21 Xplained Pro Evaluation Kit](saml21_xplained.md) | :heavy_check_mark:  | :heavy_check_mark: |
| [B-L072Z-LRWAN1 Discovery Kit](disco-l072cz.md) | :heavy_check_mark: |                   |

