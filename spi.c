/*
 * Simple SPI library for MSP430 USCI B0
 * Author: Adrian Studer
 */

//                   MSP430F552x
//                 -----------------
//            /|\ |                 |
//             |  |                 |
//    Master---+->|RST              |
//                |                 |
//                |             P3.3|-> Data Out (UCA0SIMO)
//                |                 |
//                |             P3.4|<- Data In (UCA0SOMI)
//                |                 |
//                |             P2.7|-> Serial Clock Out (UCA0CLK)

#include <msp430.h>
#include <inttypes.h>
#include "spi.h"

#define SPI_CLK		BIT7	// clock pin 2.7 SI4362 CLK
#define SPI_MISO	BIT4	// MISO pin 3.4 SI4362 SDO
#define SPI_MOSI	BIT3	// MOSI pin 3.3 SI4362 SDI

void spi_init(void)
{
    P3SEL |= SPI_MISO+SPI_MOSI;               // P3.3,4 option select
    P2SEL |= SPI_CLK;                         // P2.7 option select

    P3OUT &= ~(SPI_MOSI);
    P2OUT &= ~(SPI_CLK);

    UCA0CTL1 |= UCSWRST;                      // **Put state machine in reset**
    UCA0CTL0 |= UCMST+UCSYNC+UCCKPH+UCMSB+UCMODE_0;    // 3-pin, 8-bit SPI master
                                              // Clock polarity high, MSB
    UCA0CTL1 |= UCSSEL_2;                     // SMCLK, keeps reset
    UCA0BR0 = 5;         	                  // /25 = ca.1MHz
    UCA0BR1 = 0;                              //
    UCA0MCTL = 0;                             // No modulation
    UCA0CTL1 &= ~UCSWRST;                     // **Initialize USCI state machine**

}


