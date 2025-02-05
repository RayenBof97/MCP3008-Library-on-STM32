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
}MCP_Handler_t;

/**************************************************************************************************
 * 									APIs Supported by this driver
 *					For further informations, please check the functions definition
 **************************************************************************************************/
void MCP_Init(MCP_Handler_t *Mcp_handle,SPI_HandleTypeDef* pspi,GPIO_TypeDef *pCS_gpio,uint16_t CS_PinNumber);
void MCP_StopCommunication(MCP_Handler_t *Mcp_Handle);
void MCP_StartCommunication(MCP_Handler_t *Mcp_Handle);
void MCP_ResetCommunication(MCP_Handler_t *Mcp_Handle);
uint16_t MCP_ReadChannel(MCP_Handler_t *Mcp_Handle, uint8_t channel);

#endif /* INC_MCP_DRIVER_H_ */
