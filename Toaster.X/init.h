/* ************************************************************************** */
/** Descriptive File Name

  @Company
    Company Name

  @File Name
    filename.h

  @Summary
    Brief description of the file.

  @Description
    Describe the purpose of this file.
 */
/* ************************************************************************** */

#ifndef INIT_H
#define INIT_H




/*Fucntion prototypes*/

void initTimer(void);      //initialize timer
void initTimer1(void);    //initialize timer
void initADC(void);        //initialize ADC 
void initLeds(void);       //initialize LEDS, useful for debugging
void initOutputCompare(void); //init pwm generator
void initActuators(void);  //initialize controller outputs
/*Macros*/

/* Pic32 specific*/
#define SYSCLK  80000000L // System clock frequency, in Hz
#define PBCLOCK 40000000L // Peripheral Bus Clock frequency, in Hz
/*Register specific*/
#define flag_T1     IFS0bits.T1IF
#define flag_T2     IFS0bits.T2IF
#define flag_T3     IFS0bits.T3IF
#define flag_ADC    IFS1bits.AD1IF
#define start_ADC   AD1CON1bits.ASAM
#define ADC_value     ADC1BUF0
#define LED5         PORTCbits.RC1
#define LED_BLINK    PORTCbits.RC1=!PORTCbits.RC1
#define ZERO_CROSS   PORTCbits.RC2
#define ACTUATOR     PORTCbits.RC3

/*Program specific values*/
#define Fs      10   //ADC sampling frequency
#define F_PWM   100   //ADC sampling frequency
#define F_TIMER1 10000
/*Quality of life*/
#define HIGH        1
#define LOW         0





 
#endif
