/*
 * hsd.h
 *
 *  Created on: Mar 23, 2012
 *      Author: Роман
 */

#ifndef HSD_H_
#define HSD_H_

#define MSD_CS_LOW()     GPIO_ResetBits(GPIOE, GPIO_Pin_1)
#define MSD_CS_HIGH()    GPIO_SetBits(GPIOE, GPIO_Pin_1)

#define	CMDWRITE	    24
#define	CMDREAD			17
#define	CMDREADCSD       9

void SDSPI_Config(void);
unsigned char SDSend(unsigned char outgoing);
unsigned char CS_SDSend(unsigned char outgoing);
void CS_SDInit(void);

#endif /* HSD_H_ */
