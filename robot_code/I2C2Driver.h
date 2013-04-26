/* 
 * File:   I2C2Driver.h
 * Author: Ryan
 *
 * Created on March 25, 2013, 9:00 PM
 */

#ifndef I2C2DRIVER_H
#define	I2C2DRIVER_H

#include "i2c.h"
#include <p33FJ64GS610.h>

void IniI2C2(void);
void ReadByteI2C2(unsigned char SlaveAddr, unsigned char PointerVal, unsigned char *Byte);
void ReadBurstI2C2(unsigned char SlaveAddr, unsigned char PointerVal, unsigned char* Bytes, int Number);
void WriteByteI2C2(unsigned char SlaveAddr, unsigned char PointerVal, unsigned char Byte);

#endif	/* I2C2DRIVER_H */

