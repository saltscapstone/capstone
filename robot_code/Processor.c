#include "Processor.h"

/*
 *Initialization code for the PIC33F
 *
 * This code fools with:
 * Oscillator
 * IO Ports
 * Interrupts
 *
 * All initialization may be done by running IniProcessor();
 */
void IniOsc(void)
{
    /* Configure Oscillator to operate the device at 40Mhz
	   Fosc= Fin*M/(N1*N2), Fcy=Fosc/2
 	   Fosc= 7.37*(43)/(2*2)=80Mhz for Fosc, Fcy = 40Mhz */

	/* Configure PLL prescaler, PLL postscaler, PLL divisor */
	PLLFBD=41; 				/* M = PLLFBD + 2 */
	CLKDIVbits.PLLPOST=0;   /* N1 = 2 */
	CLKDIVbits.PLLPRE=0;    /* N2 = 2 */

    __builtin_write_OSCCONH(0x01);			/* New Oscillator FRC w/ PLL */
    __builtin_write_OSCCONL(0x01);  		/* Enable Switch */

	while(OSCCONbits.COSC != 0b001);		/* Wait for new Oscillator to become FRC w/ PLL */
    while(OSCCONbits.LOCK != 1);			/* Wait for Pll to Lock */

	/* Now setup the ADC and PWM clock for 120MHz
	   ((FRC * 16) / APSTSCLR ) = (7.37 * 16) / 1 = ~ 120MHz*/

	ACLKCONbits.FRCSEL = 1;					/* FRC provides input for Auxiliary PLL (x16) */
	ACLKCONbits.SELACLK = 1;				/* Auxiliary Oscillator provides clock source for PWM & ADC */
	ACLKCONbits.APSTSCLR = 7;				/* Divide Auxiliary clock by 1 */
	ACLKCONbits.ENAPLL = 1;					/* Enable Auxiliary PLL */

	while(ACLKCONbits.APLLCK != 1);			/* Wait for Auxiliary PLL to Lock */

}

void IniIO(void)
{
    //TRISAbits.TRISA2 = 1;
    //TRISAbits.TRISA3 = 1;
}

void IniInterrupts(void)
{
    SRbits.IPL = 0;  //Set non interrupt code to lowest priority
    INTCON1bits.NSTDIS = 0;  //Enable interrupt nesting

    IPC0bits.INT0IP = 0;  //Priorities for all external interrupts.  Only Set ones for MPU and Beagle Comms
    IPC5bits.INT1IP = 0;
    IPC7bits.INT2IP = 0;
    IPC13bits.INT3IP = 0;
    IPC13bits.INT4IP = 0;

    INTCON2bits.INT0EP = 0;  //Interrupt on positive edge
    INTCON2bits.INT1EP = 0;
    INTCON2bits.INT2EP = 0;
    INTCON2bits.INT3EP = 0;
    INTCON2bits.INT4EP = 0;

    IFS0bits.INT0IF = 0;  //Clear all interrupt requests
    IFS1bits.INT1IF = 0;
    IFS1bits.INT2IF = 0;
    IFS3bits.INT3IF = 0;
    IFS3bits.INT4IF = 0;

    IEC0bits.INT0IE = 0;  //set them to one and let them fly
    IEC1bits.INT1IE = 0;
    IEC1bits.INT2IE = 0;
    IEC3bits.INT3IE = 0;
    IEC3bits.INT4IE = 0;

}

void IniProcessor(void)
{
    IniOsc();
    IniIO();
}

/*
 * Interrupt handlers for running ISRs
 */

void __attribute__((interrupt, no_auto_psv)) _INT0Interrupt(void)
{
    //Insert ISR Code Here

    //Enable this once interrupt code is happy.  Put a read in here to clear
    //the interrupt bit on the MPU

    //ISRHandlerMPU6050();

    IFS0bits.INT0IF = 0; //Clear interrupt flag
}