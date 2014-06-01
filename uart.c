/*
 * Simple UART library for MSP430 USCI A0 - so far TX only
 * Author: Adrian Studer
 */

#include <msp430.h>
#include <inttypes.h>
#include "uart.h"

void uart_init(void)
{
	  P4SEL |= BIT4+BIT5;                       // P4.4,5 = USCI_A1 TXD/RXD
	  UCA1CTL1 |= UCSWRST;                      // **Put state machine in reset**
	  UCA1CTL1 |= UCSSEL_2;                     // SMCLK
	  UCA1BR0 = 217; // 35 4mhz          // SMCLK MHz / 115200 (see User's Guide)
	  UCA1BR1 = 0;                              // SMCLK MHz / 115200
	  UCA1MCTL |= UCBRS_1 + UCBRF_0;            // Modulation UCBRSx=1, UCBRFx=0
	  UCA1CTL1 &= ~UCSWRST;                     // **Initialize USCI state machine**
}

void uart_send_string(const char* buffer)
{
	uint16_t i = 0;
	while (buffer[i])
	{
		while (!(UCA1IFG&UCTXIFG));					// wait for UART to be ready for TX
		UCA1TXBUF = buffer[i];
		i++;
	}
}

void uart_send_byte(uint8_t data)
{
	while (!(UCA1IFG&UCTXIFG));					// wait for UART to be ready for TX
	UCA1TXBUF = data;
}

