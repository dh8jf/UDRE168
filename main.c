/*
Title:			Main
Autor:			Frank Jonischkies
Umgebung:		WinAVR-20070122
*/ 

#include <inttypes.h>
#include <avr/io.h>
#include <avr/interrupt.h>
#include <avr/pgmspace.h>

#include "uart.h"

int main(void) {
	InitUART();
	sei();
	
	UartPutS("Eine Zeichenkette\n\r");
	UartPutP(PSTR("Noch eine Zeichenkette\n\r"));
	UartPutC('a');

	for(;;) {
	}
}
