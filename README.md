
# **UART Driver TX for STM32 F4**
This is a UART (Universal Asynchronous Receiver/Transmitter) driver's transmit functionality for the STM32 F4 microcontroller, implemented in C. The driver provides a simple and efficient way to send data over the UART interface.

## **_Features_**
___
* Supports full-duplex communication over the UART interface.
* Provides a straightforward API for transmitting data.
* Supports blocking and non-blocking transmit operations.
* Configurable `baud rate` and `system Cock`
```

void set_baudRate(uint32_t PeriphCLK, uint32_t baudRate) {
	*USART2_BRR = compute_bd(PeriphCLK, baudRate);
}
```
* Efficient and optimized code for improved performance.

