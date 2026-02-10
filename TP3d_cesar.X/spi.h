/* SPI Explorer 8 (PIC16F1719) */

#ifndef _SPI_H
#define _SPI_H

#define DUMMY_DATA 0x0

void SPI_InitializePins(void);
void SPI_Initialize(void);
char SPI_Exchange8bit(char data);
char SPI_Exchange8bitBuffer(char *dataIn, char bufLen, char *dataOut);
char SPI_IsBufferFull(void);
char SPI_HasWriteCollisionOccured(void);
void SPI_ClearWriteCollisionStatus(void);


#endif // _SPI_H
