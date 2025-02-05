/*
 * MCP_Driver.h
 *
 *  Created on: Feb 4, 2025
 *      Author: Rayen
 */

#ifndef INC_MCP_DRIVER_H_
#define INC_MCP_DRIVER_H_

/* Includes ------------------------------------------------------------------*/
#include "stm32f1xx_hal.h"


typedef struct{
	SPI_HandleTypeDef* hspi;									/*!<Assign The SPI Over which The communication is being held */
	GPIO_TypeDef *CS_gpio;										/*!<Assign The GPIO Over which CS is connected , Macros in @addtogroup Peripheral_declaration */
	uint16_t CS_PinNumber;										/*!<Assign The Pin Number  Over which CS is connected*/
	uint8_t MCP_Mode;											/*!<Assign the MCP Mode , Macros in @Single/Diff Mode*/
}MCP_Handler_t;


/*
 * @Single/Diff Mode
 */
#define MCP_SINGLE_ENDED_MODE	1
#define MCP_DIFFERENTIAL_ENDED_MODE	0

/*
 * @MCP_Channels
 */
#define MCP_Channel_0	0
#define MCP_Channel_1	1
#define MCP_Channel_2	2
#define MCP_Channel_3	3
#define MCP_Channel_4	4
#define MCP_Channel_5	5
#define MCP_Channel_6	6
#define MCP_Channel_7	7


/**************************************************************************************************
 * 									APIs Supported by this driver
 *					For further informations, please check the functions definition
 **************************************************************************************************/
void MCP3008_Init(MCP_Handler_t *Mcp_handle,SPI_HandleTypeDef* hspi,GPIO_TypeDef *pCS_gpio,uint16_t CS_PinNumber,uint8_t MCP_Mode);
void MCP3008_StopCommunication(MCP_Handler_t *Mcp_Handle);
void MCP3008_StartCommunication(MCP_Handler_t *Mcp_Handle);
void MCP3008_ResetCommunication(MCP_Handler_t *Mcp_Handle);
uint16_t MCP3008_ReadChannel(MCP_Handler_t *Mcp_Handle, uint8_t channel);

#endif /* INC_MCP_DRIVER_H_ */
