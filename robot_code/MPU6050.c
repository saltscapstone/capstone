#include "MPU6050.h"
#include "I2C2Driver.h"
#include <float.h>

float dt;

void IniMPU6050(void)
{
    IniI2C2();

    //Make sure the macros work when they don't write the whole register...

    WriteByteI2C2(MPU60X0_ADDRESS_AD0_LOW, MPU60X0_RA_SMPLRT_DIV, 0x00);  //Don't divide sample rate off gyro
    WriteByteI2C2(MPU60X0_ADDRESS_AD0_LOW, MPU60X0_RA_CONFIG, 0x01);    //Set gyro sample rate to 1kHz
    WriteByteI2C2(MPU60X0_ADDRESS_AD0_LOW, MPU60X0_RA_GYRO_CONFIG, MPU60X0_GYRO_FS_500);  //set gyro full scale
    WriteByteI2C2(MPU60X0_ADDRESS_AD0_LOW, MPU60X0_RA_ACCEL_CONFIG, MPU60X0_ACCEL_FS_4);  //set accel full scale

    /*
     * The next few writes configure the interrupt pins.  Enable this only
     * after making sure all the other initialization code works...
     */

    //WriteByteI2C2(MPU60X0_ADDRESS_AD0_LOW, MPU60X0_RA_INT_PIN_CFG, 0b00110000);  //Active high, push pull, hold high until clear, clear on any read, no FIFO
    //WriteByteI2C2(MPU60X0_ADDRESS_AD0_LOW, MPU60X0_RA_INT_ENABLE, 0x01);    //Interrupt on data ready, does not need FIFO



    
    WriteByteI2C2(MPU60X0_ADDRESS_AD0_LOW,0x6B,0x00);      //Bring it out of sleep mode
}


/*
 * This updates position and velocity every time the interrupt fires.
 * Data is stored in matrix form, so that rotation, acceleration, velocity, and
 * position matricies can be computed in one shot.
 * 
 * The bytes from the MPU need to be converted to signed ints, then to fractionals
 */
void ISRHandlerMPU6050(void)
{
    AngularPosition.x = AngularVelocity.x*dt;
    AngularPosition.y = AngularVelocity.y*dt;
    AngularPosition.z = AngularVelocity.z*dt;
}