#ifndef UART_H
#define UART_H

/* 
	UART
*/

#define UART_BAUD_RATE 9600

#define TX_BUFFER_SIZE 32
#define TX_BUFFER_MASK (TX_BUFFER_SIZE - 1)

void InitUART(void);

void UartPutC(char data);
void UartPutS(const char *s);
void UartPutP(const char *progmem_s);

#endif // UART_H
