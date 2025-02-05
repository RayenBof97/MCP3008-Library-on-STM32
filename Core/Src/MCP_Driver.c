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
* You application should include STM HAL.
*
*
*/
/*INCLUDES*/
#include "MCP_Driver.h"

/********************************************************************
 * @fn				-  MCP3008_StartCommunication
 *
 * @brief			- Initialise the MCP Handler
 *
 * @param[in]		- Address of MCP_Handle (Declared in the application)
 * @param[in]		- Address of spi_Handle (Declared in the application using HAL)
 * @param[in]		- Address of GPIO used for Chip Select (Declared in the application)
 * @param[in]		- Chip select Pin Number (Use the HAL Macros)
 * #param[in]		- MCP Mode (@MCP_Mode)
 *
 * @return 			- NONE
 *
 * @note			- NONE
 */
void MCP3008_Init(MCP_Handler_t *Mcp_handle,SPI_HandleTypeDef* hspi,GPIO_TypeDef *pCS_gpio,uint16_t CS_PinNumber,uint8_t MCP_Mode){

	Mcp_handle->CS_PinNumber = CS_PinNumber;
	Mcp_handle->CS_gpio = pCS_gpio;
	Mcp_handle->hspi = hspi;
	Mcp_handle->MCP_Mode = MCP_Mode;

}

/********************************************************************
 * @fn				-  MCP3008_StartCommunication
 *
 * @brief			- Reset the communication
 *
 * @param[in]		- Address of MCP_Handle (Declared in the application)
 *
 * @return 			- NONE
 *
 * @note			- NONE
 */
void MCP3008_StartCommunication(MCP_Handler_t *Mcp_Handle){
	HAL_GPIO_WritePin(Mcp_Handle->CS_gpio, Mcp_Handle->CS_PinNumber, GPIO_PIN_RESET);
}


/********************************************************************
 * @fn				-  MCP3008_StopCommunication
 *
 * @brief			- Reset the communication
 *
 * @param[in]		- Address of MCP_Handle (Declared in the application)
 *
 * @return 			- NONE
 *
 * @note			- NONE
 */
void MCP3008_StopCommunication(MCP_Handler_t *Mcp_Handle){
	HAL_GPIO_WritePin(Mcp_Handle->CS_gpio, Mcp_Handle->CS_PinNumber, GPIO_PIN_SET);
}


/********************************************************************
 * @fn				- MCP3008_ResetCommunication
 *
 * @brief			- Reset the communication
 *
 * @param[in]		- Address of MCP_Handle (Declared in the application)
 *
 * @return 			- NONE
 *
 * @note			- NONE
 */
void MCP3008_ResetCommunication(MCP_Handler_t *Mcp_Handle){
	HAL_GPIO_WritePin(Mcp_Handle->CS_gpio, Mcp_Handle->CS_PinNumber, GPIO_PIN_SET);
	HAL_GPIO_WritePin(Mcp_Handle->CS_gpio, Mcp_Handle->CS_PinNumber, GPIO_PIN_RESET);
}


/********************************************************************
 * @fn				- MCP3008_ReadChannel
 *
 * @brief			- Read a channel of the MCP
 *
 * @param[in]		- Address of MCP_Handle (Declared in the application)
 * @param[in]		- channel (Chosen from @MCP_Channels)
 *
 * @return 			- Sampled data ( on 10 Bits)
 *
 * @note			- This function is specified for MCP3008
 */
uint16_t MCP3008_ReadChannel(MCP_Handler_t *Mcp_Handle, uint8_t channel){
	uint8_t txData[3], rxData[3];
	uint16_t adcResult;

	if (channel > 7) return 0;  // Invalid channel, return 0

    txData[0] = 0x01;             								 // Start bit
    txData[1] = (Mcp_Handle->MCP_Mode << 7) | (channel << 4);    // Mode selection and Channel selection
    txData[2] = 0x00;                             				 // Dummy byte for clock cycles

	//Start Communication
	MCP_StartCommunication(Mcp_Handle);
	// Full-Duplex transmission (send txData, receive rxData)
	if (HAL_SPI_TransmitReceive(Mcp_Handle->hspi, txData, rxData, 3, HAL_MAX_DELAY) != HAL_OK) {
	        MCP_StopCommunication(Mcp_Handle);
	        return 0; //SPI Error
	    }
	//Close Communication
	MCP_StopCommunication(Mcp_Handle);

	adcResult = ((uint16_t)rxData[1] << 8) | rxData[2];
	adcResult &= 0x03FF; //Masking Bits

	return adcResult;
}


