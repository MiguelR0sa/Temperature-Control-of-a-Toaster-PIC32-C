/* ************************************************************************** */
/** Descriptive File Name

  @Company
    Company Name

  @File Name
    filename.c

  @Summary
    Brief description of the file.

  @Description
    Describe the purpose of this file.
 */
//#include "config_bits.h"

#include "init.h"

#include <xc.h>
#include <stdint.h>
#include <stdbool.h>
#include <sys/attribs.h>
#include <stdio.h>
#include <stdlib.h>

void initADC(void )  //timer t2
{
    
    /*ADC Configuration*/
   // Disable JTAG interface as it uses a few ADC ports
    DDPCONbits.JTAGEN = 0;
    
    
    //Scan mode configuration
    AD1CON2bits.CSCNA=1;// Scan Input Selections for CH0+ SHA Input for MUX A Input Multiplexer Setting bit
    AD1CON2bits.ALTS=0; //Always use MUX A input multiplexer settings
    //Analog inputs configuration
    TRISBbits.TRISB0 = 1; // Set AN0 to input mode
    AD1PCFGbits.PCFG0 = 0; // Set AN0 to analog mode,
 
    //Choose mux A inputs 
     AD1CSSL= 0x0000001; //select AN0 and AN1 for input scan  
     
    
    
    // Generic part
    AD1CON1bits.SSRC = 7; // Internal counter ends sampling and starts conversion
    AD1CON1bits.CLRASAM = 1; //Stop conversion when 1st A/D converter interrupt is generated and clears ASAM bit automatically
    AD1CON1bits.FORM = 0; // Integer 16 bit output format
    AD1CON2bits.VCFG = 0; // VR+=AVdd; VR-=AVss
    AD1CON2bits.SMPI = 2; // Number (+1) of consecutive conversions, stored in ADC1BUF0...ADCBUF{SMPI}
    AD1CON3bits.ADRC = 1; // ADC uses internal RC clock
    AD1CON3bits.SAMC = 8; // Sample time is 8TAD ( TAD = 100ns), enough to acomodate 2 consecutive samples
       
    
    // Enable module
    AD1CON1bits.ON = 1; // Enable A/D module (This must be the ***last instruction of configuration phase***)


 
}
void initTimer(void)
{
    T2CONbits.TCKPS = 7;  //prescaler=8, big enough to accomodate [100-500]hz sampling freqency
    PR2 = PBCLOCK/(Fs*256);  
    TMR2 = 0;
    T2CONbits.TON = 1;
}
void initTimer1(void)
{
    T1CONbits.TCKPS = 1;  //prescaler=8, big enough to accomodate [100-500]hz sampling freqency
    PR1 = PBCLOCK/(F_TIMER1*8);  
    TMR1 = 0;
    T1CONbits.TON = 1;
}

void initActuators(void)
{
    TRISCbits.TRISC2 = 1; /* Set RC2 as an input */  
    TRISCbits.TRISC3 = 0; /* Set RC3 as an out */  
}
void initOutputCompare(void)
{
    // Set RD0 as digital output
    TRISDbits.TRISD0 = 0;
    PORTDbits.RD0 = 1;
  
    // Set timer
    T3CONbits.ON = 0; // Stop timer
    IFS0bits.T3IF=0; // Reset interrupt flag    
    T3CONbits.TCKPS = 3; //Select pre-scaler
   // T3CONbits.T32 = 0; // 16 bit timer operation
    PR3=PBCLOCK/(F_PWM*8); ; // Compute PR value
    TMR3=0;

    // Set OC1
    OC1CONbits.OCM = 6; // OCM = 0b110 : OC1 in PWM mode,
    OC1CONbits.OCTSEL=1; // Timer 2 is clock source of OCM
    OC1RS=0; // Compute OC1xRS value
    OC1CONbits.ON=1;     // Enable OC1

    // Start PWM generation
    T3CONbits.TON=1; // Start the timer

}

void initLeds(void)
{
    TRISCbits.TRISC1 = 0; //LED5
}