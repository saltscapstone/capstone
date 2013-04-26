/* 
 * File:   Processor.h
 * Author: Ryan
 *
 * Created on March 28, 2013, 11:37 AM
 */

#ifndef PROCESSOR_H
#define	PROCESSOR_H

#include <p33FJ64GS610.h>
#include "MPU6050.h"

void IniOsc(void);
void IniIO(void);
void IniProcessor(void);

void __attribute__((__interrupt__)) _INT0Interrupt(void);


#endif	/* PROCESSOR_H */

