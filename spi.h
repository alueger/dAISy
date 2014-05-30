/*
 * Simple SPI library for MSP430 USCI B0
 * Author: Adrian Studer
 */

#ifndef SPI_H_
#define SPI_H_

void spi_init(void);

inline uint8_t spi_transfer(const uint8_t data)
{
	UCA0TXBUF = data;
	while (UCA0STAT & UCBUSY);
	return UCA0RXBUF;
}

#endif /* SPI_H_ */
