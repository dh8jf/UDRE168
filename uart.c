/*
Title:			UART
Autor:			Frank Jonischkies
Umgebung:		WinAVR-20070122
*/ 

#include <inttypes.h>
#include <avr/io.h>
#include <avr/interrupt.h>
#include <avr/pgmspace.h>

#include "uart.h"

// Globale Variablen
static char TxBuff[TX_BUFFER_SIZE];

static volatile uint8_t TxRead;		// Zeigt auf Zeichen, das gesendet werden soll
static uint8_t TxWrite;				// Zeigt auf nächste Schreibposition im Puffer

// Funktionen Öffentlich
void InitUART(void) {
	UBRR0L = (F_CPU/(16L*UART_BAUD_RATE))-1;
	UCSR0B = (1<<TXEN0);									// UART TX einschalten
}

void UartPutC(char data) {
	uint8_t temp = (TxWrite + 1) & TX_BUFFER_MASK;
	while(temp == TxRead);									// Warte bis Platz im Puffer
	TxWrite = temp;
	TxBuff[temp] = data;
	UCSR0B |= (1<<UDRIE0);									// UDRE Interrupt ein
}
/*
void UartPutC(char data) {
	while(!(UCSR0A & (1<<UDRE0)));
	UDR0 = data;
}
*/
void UartPutS(const char *s) {
	while(*s) UartPutC(*s++);
}

void UartPutP(const char *progmem_s) {
	register char c;
	while((c = pgm_read_byte(progmem_s++))) UartPutC(c);
}

// Interrupt Service Routine
ISR(USART_UDRE_vect) {
	if(TxRead != TxWrite) {
		uint8_t temp = (TxRead + 1) & TX_BUFFER_MASK;
		TxRead = temp;
		UDR0 = TxBuff[temp];								// nächtes Zeichen aus Puffer senden
	} else UCSR0B &= ~(1<<UDRIE0);							// UDRE Interrupt aus
}
