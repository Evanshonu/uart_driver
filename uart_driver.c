#include<stdint.h>
#include<stdio.h>
/** the RCC   Register **/
uint32_t *RCC_AHB1ENR = ((uint32_t*) (0x40023800UL + 0x30UL));
/** The MODER Register **/
uint32_t *GPIOA_MODER = ((uint32_t*) (0x40020000UL + 0000UL));
/** The ODR   Register **/
uint32_t *GPIOA_ODR = ((uint32_t*) (0x40020000UL + 0x14UL));
/**The GPIOx_AFRL Register***/
uint32_t *GPIOA_AFRL = ((uint32_t*) (0x40020000UL + 0x20UL));
/**The RCC_APB1ENR register**/
uint32_t *RCC_APB1ENR_USARTEN = ((uint32_t*) (0x40023800UL + 0x40UL));

/**The USART2 registers	**/
uint32_t *USART2_SR = ((uint32_t*) (0x40004400UL + 0x00UL));
uint32_t *USART2_DR = ((uint32_t*) (0x40004400UL + 0x04UL));
uint32_t *USART2_BRR = ((uint32_t*) (0x40004400UL + 0x08UL));
uint32_t *USART2_CR1 = ((uint32_t*) (0x40004400UL + 0x0CUL));
uint32_t *USART2_CR2 = ((uint32_t*) (0x40004400UL + 0x10UL));

void set_baudRate(uint32_t PeriphCLK, uint32_t baudRate);
uint32_t compute_bd(uint32_t PeriphCLK, uint32_t baudRate);
void uart_tx_init(void);
void transmitString(int character);
int checkTransmittionComplete(void);
int main(void) {
	*RCC_AHB1ENR |= (1UL << 0);
	*GPIOA_MODER |= (1UL << 10);
	int checkValue; /**Checking if transmission is complete**/
	uart_tx_init();
	while (1) {
		*GPIOA_ODR |= (1UL << 5);


		checkValue = checkTransmittionComplete();
		if (checkValue) {
			*GPIOA_ODR ^= (1UL << 5);
			for (int i = 0; i < 100000; i++) {}
			printf("Hello Evans From Stm32\n\r");
		} else {
			*GPIOA_ODR &= ~(1UL << 5);

		}
	}

}
void transmitString(int character) {
	/**Check whether the transmit data register not empty!**/
	while ((*USART2_SR & (1UL << 7)) == 0) {
	}

	/**Write 8bit to the data register**/
	*USART2_DR = (character & 0xFF);
}
void uart_tx_init(void) {
	/**Enable clock access for GPIOA***/
	*RCC_AHB1ENR |= (1UL << 0);
	/**Set PA2 MODER to alternate Function MODE***/
	*GPIOA_MODER |= (1UL << 5);
	/**Set Alternate Function Type to AF07***/
	*GPIOA_AFRL |= (1UL << 8);
	*GPIOA_AFRL |= (1UL << 9);
	*GPIOA_AFRL |= (1UL << 10);
	/**Enable clock access to the USART module***/
	*RCC_APB1ENR_USARTEN |= (1UL << 17);
	/**Configure the baud Rate***/
	set_baudRate(16000000, 9600); /***You can change the baud rate for your application requirement***/
	/**Enable the transfer direction as TX***/
	*USART2_CR1 = (1UL << 3);
	/**Enable the UART Module***/
	*USART2_CR1 |= (1UL << 13);

}
void set_baudRate(uint32_t PeriphCLK, uint32_t baudRate) {
	*USART2_BRR = compute_bd(PeriphCLK, baudRate);
}

uint32_t compute_bd(uint32_t PeriphCLK, uint32_t baudRate) {
	return ((PeriphCLK + (baudRate / 2U)) / baudRate);
}
int checkTransmittionComplete(void) {
	if (*USART2_SR & ((1UL << 6)))
		return 1;
}
