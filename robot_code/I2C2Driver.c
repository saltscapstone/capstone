#include "I2C2Driver.h"

void IniI2C2(void)
{
    I2C2BRG = 0x188; //sets bus speed.  crank this mother up
    I2C2CON = 0xD020;
//    I2C2CONbits.I2CEN = 1;
//    I2C2CONbits.I2CSIDL = 0;
//    I2C2CONbits.IPMIEN = 0;
//    I2C2CONbits.A10M = 0;
//    I2C2CONbits.DISSLW = 0;
//    I2C2CONbits.I2CSIDL = 0;
//    I2C2CONbits.ACKDT = 0; //this was 1...


}

void ReadByteI2C2(unsigned char SlaveAddr, unsigned char PointerVal, unsigned char* Byte)
{
    IdleI2C2();
    StartI2C2();
    while(I2C2CONbits.SEN);

    MasterWriteI2C2(SlaveAddr << 1);
    while(I2C2STATbits.TRSTAT);
    while(I2C2STATbits.ACKSTAT);

    MasterWriteI2C2(PointerVal);
    while(I2C2STATbits.TRSTAT);
    while(I2C2STATbits.ACKSTAT);

    RestartI2C2();
    while(I2C2CONbits.RSEN);
    MasterWriteI2C2((SlaveAddr << 1)+1);
    while(I2C2STATbits.TRSTAT);
    while(I2C2STATbits.ACKSTAT);

    while(I2C2CONbits.RCEN);
    *Byte = MasterReadI2C2();

    NotAckI2C2();
    StopI2C2();
    while(I2C2CONbits.PEN);
}

void ReadBurstI2C2(unsigned char SlaveAddr, unsigned char PointerVal, unsigned char* Bytes, int Number)
{
    IdleI2C2();
    StartI2C2();
    while(I2C2CONbits.SEN);

    MasterWriteI2C2(SlaveAddr << 1);
    while(I2C2STATbits.TRSTAT);
    while(I2C2STATbits.ACKSTAT);

    MasterWriteI2C2(PointerVal);
    while(I2C2STATbits.TRSTAT);
    while(I2C2STATbits.ACKSTAT);

    RestartI2C2();
    while(I2C2CONbits.RSEN);
    MasterWriteI2C2((SlaveAddr << 1)+1);
    while(I2C2STATbits.TRSTAT);
    while(I2C2STATbits.ACKSTAT);

    while (Number > 0)
    {
        while(I2C2CONbits.RCEN);
        *Bytes = MasterReadI2C2();
        Bytes++;                            //Move up to point to the next byte
        Number--;                           //Decrement counter
    }

    NotAckI2C2();
    StopI2C2();
    while(I2C2CONbits.PEN);
}

void WriteByteI2C2(unsigned char SlaveAddr, unsigned char PointerVal, unsigned char Byte)
{
    IdleI2C2();
    StartI2C2();
    while(I2C2CONbits.SEN);

    MasterWriteI2C2(SlaveAddr << 1);
    while(I2C2STATbits.TRSTAT);
    while(I2C2STATbits.ACKSTAT);

    MasterWriteI2C2(PointerVal);
    while(I2C2STATbits.TRSTAT);
    while(I2C2STATbits.ACKSTAT);

    MasterWriteI2C2(Byte);
    while(I2C2STATbits.TRSTAT);
    while(I2C2STATbits.ACKSTAT);

    StopI2C2();
    while(I2C2CONbits.PEN);
}