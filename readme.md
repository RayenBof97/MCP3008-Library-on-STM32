# MCP3008 Driver Library

This repository contains a custom driver library for the MCP3008 ADC (Analog-to-Digital Converter). It provides basic and modular functions to configure and interact with the MCP3008 for my future projects.
The chip is provided by Microchip and you can find its datasheet [in this link.](https://cdn-shop.adafruit.com/datasheets/MCP3008.pdf) 

## Clone the Repository  
If you're interested in exploring the code, you can clone this repository to your STM32CubeIDE workspace using the following command:  
```bash
git clone https://github.com/RayenBof97/MCP3008-Library-on-STM32
```

## API Reference

#### MCP Initialization

```c
void MCP3008_Init(MCP_Handler_t *Mcp_handle, SPI_HandleTypeDef* hspi, GPIO_TypeDef *pCS_gpio, uint16_t CS_PinNumber, uint8_t MCP_Mode)
```

| Parameter       | Type                 | Description                                                                 |
| :-------------- | :------------------- | :-------------------------------------------------------------------------- |
| `Mcp_handle`    | `MCP_Handler_t*`     | **Required**. Pointer to the MCP handler structure.                         |
| `hspi`          | `SPI_HandleTypeDef*` | **Required**. SPI handle used for communication.                            |
| `pCS_gpio`      | `GPIO_TypeDef*`      | **Required**. GPIO port used for chip select (CS).                          |
| `CS_PinNumber`  | `uint16_t`           | **Required**. Chip select pin number.                                       |
| `MCP_Mode`      | `uint8_t`            | **Required**. MCP operating mode.                                           |

#### Start Communication

```c
void MCP3008_StartCommunication(MCP_Handler_t *Mcp_Handle)
```

| Parameter       | Type             | Description                                                  |
| :-------------- | :--------------- | :----------------------------------------------------------- |
| `Mcp_Handle`    | `MCP_Handler_t*` | **Required**. Pointer to the MCP handler structure.           |

#### Stop Communication

```c
void MCP3008_StopCommunication(MCP_Handler_t *Mcp_Handle)
```

| Parameter       | Type             | Description                                                  |
| :-------------- | :--------------- | :----------------------------------------------------------- |
| `Mcp_Handle`    | `MCP_Handler_t*` | **Required**. Pointer to the MCP handler structure.           |

#### Reset Communication

```c
void MCP3008_ResetCommunication(MCP_Handler_t *Mcp_Handle)
```

| Parameter       | Type             | Description                                                  |
| :-------------- | :--------------- | :----------------------------------------------------------- |
| `Mcp_Handle`    | `MCP_Handler_t*` | **Required**. Pointer to the MCP handler structure.           |

#### Read Channel

```c
uint16_t MCP3008_ReadChannel(MCP_Handler_t *Mcp_Handle, uint8_t channel)
```

| Parameter       | Type             | Description                                                  |
| :-------------- | :--------------- | :----------------------------------------------------------- |
| `Mcp_Handle`    | `MCP_Handler_t*` | **Required**. Pointer to the MCP handler structure.           |
| `channel`       | `uint8_t`        | **Required**. Channel number to read from the MCP3008.        |

---


## Contributing
Contributions are welcome! If you'd like to report bugs, suggest features, or submit improvements, please open an issue or create a pull request.

## License
This project is licensed under the MIT License. See the LICENSE file for details.

                   