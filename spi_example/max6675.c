/*
 * max6675.c
 *
 *  Created on: Mar 2, 2021
 *      Author: ber-a
 */

#include "max6675.h"
#include "main.h"

void initSPI2(void)
{
	//Define SPI2 PIN PB13, PB14 & PB15
	GPIOB->MODER &= 0xABFFFFFF;

	// Enable SPI2
	RCC->APB1ENR1 |= (1 << 14);

	// Set pin mode very high speed
	GPIOB->OSPEEDR |= 0xFC000000;

	// Choose AF5 for SPI2 Alternate function register
	GPIOB->AFR[1] |= (0x5 << 20);  // for pin 13
	GPIOB->AFR[1] |= (0x5 << 24);  // for pin 14
	GPIOB->AFR[1] |= (0x5 << 28);  // for pin 15

	// Define SPI2 clock
	SPI2->CR1 |= (1 << 5);

	// Define mode SPI in 0
	SPI2->CR1 |= (0 << 1);  // CPOL 0
	SPI2->CR1 |= (0 << 0);  // CPHA 0

	// Set data size to 16 bits
	SPI2->CR2 |= (0xF << 8);

	// Set mater mode
	SPI2->CR1 |= (1 << 2);

	// software slave management
	SPI2->CR1 |= (1 << 9);
	SPI2->CR1 |= (1 << 8);

	// Enable SPI2
	SPI2->CR1 |= (1 << 6);

	//wait while initialize
	HAL_Delay(100);
}

uint16_t ReadTemp(void)
{
	uint16_t sTemp;

	// Set CS low
	HAL_GPIO_WritePin(CS_GPIO_Port, CS_Pin, GPIO_PIN_RESET);

	// Send Data
	*(uint16_t*)&SPI2->DR = 0x0A0A;

	// While until transmist is empty
	while(!(SPI2->SR & (1 << 1)));

	// wait busy
	while((SPI2->SR & (1 << 7)));

	// Read Data
	sTemp = *(uint16_t*)&SPI2->DR;

	// Set CS High
	HAL_GPIO_WritePin(CS_GPIO_Port, CS_Pin, GPIO_PIN_SET);

	// Begin student code

	// End student code


	return sTemp;

}
