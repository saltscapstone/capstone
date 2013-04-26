/* 
 * File:   main.c
 * Author: Ryan
 *
 * Created on March 19, 2013, 7:07 PM
 */

#include <stdlib.h>
#include "p33FJ64GS610.h"

#include "Processor.h"
#include "MPU6050.h"

/* Configuration Bit Settings */
_FOSCSEL(FNOSC_FRC)
_FOSC(FCKSM_CSECMD & OSCIOFNC_ON)
_FWDT(FWDTEN_OFF)
_FPOR(FPWRT_PWR128)
_FICD(ICS_PGD1 & JTAGEN_OFF)


//shittiest code ever
int tempcomp;
float temp;
unsigned char hightemp;
unsigned char lowtemp;

int main()
{

    IniProcessor();
    IniMPU6050();


    while(1)    /* Infinite Loop */
    {
        CloseI2C2();
        OpenI2C2(0xD020,0x0188);
        ReadByteI2C2(0x68, 0x41, &hightemp);
        ReadByteI2C2(0x68, 0x42, &lowtemp);
        tempcomp = (hightemp << 8) + lowtemp;
        temp = (tempcomp/340) + 36.53;
    }
}

