/*
 *
  ******************************************************************************
  * @file    MCP_Driver.c
  * @author  Rayen	Bouafif
  * @mail    bouafifrayen01@gmail.com
  * @Tel     (+216)29 049 373
  * @date    04-05-2025
  *****************************************************************************
* This File Also contain the APIs explanation in the comments
*/
/*INCLUDES*/
#include "MCP_Driver.h"

void MCP_Init(MCP_Handler_t *Mcp_handle,SPI_HandleTypeDef* pspi,GPIO_TypeDef *pCS_gpio,uint_t CS_PinNumber){
	Mcp_handle->CS_PinNumber = CS_PinNumber;
	Mcp_handle->CS_gpio = pCS_gpio;
	Mcp_handle->hspi = pspi;
}

void MCP_StartCommunication(MCP_Handler_t *Mcp_Handle){
	HAL_GPIO_WritePin(Mcp_Handle->CS_gpio, Mcp_Handle->CS_PinNumber, GPIO_PIN_RESET);
}

void MCP_StopCommunication(MCP_Handler_t *Mcp_Handle){
	HAL_GPIO_WritePin(Mcp_Handle->CS_gpio, Mcp_Handle->CS_PinNumber, GPIO_PIN_SET);
}


void MCP_ResetCommunication(MCP_Handler_t *Mcp_Handle){
	HAL_GPIO_WritePin(Mcp_Handle->CS_gpio, Mcp_Handle->CS_PinNumber, GPIO_PIN_SET);
	HAL_GPIO_WritePin(Mcp_Handle->CS_gpio, Mcp_Handle->CS_PinNumber, GPIO_PIN_RESET);
}


uint16_t MCP_ReadChannel(MCP_Handler_t *Mcp_Handle, uint8_t channel){
	uint8_t txData[3], rxData[3];
	uint16_t adcResult;

    txData[0] = 0x01;                              // Start bit
    txData[1] = 0x80 | (channel << 4);             // SGL/DIFF = 1 (single-ended), Channel selection
    txData[2] = 0x00;                              // Dummy byte for clock cycles

	//Start Communication
	MCP_StartCommunication(Mcp_Handle);
	// Full-Duplex transmission (send txData, receive rxData)
	HAL_SPI_TransmitReceive(Mcp_Handle->hspi, txData, rxData, 3, HAL_MAX_DELAY);
	//Close Communication
	MCP_StopCommunication(Mcp_Handle);

	adcResult = ((uint16_t)rxData[1] << 8) | rxData[2]; //
	adcResult &= 0x07FF; //Masking Bits

	return adcResult;
}


