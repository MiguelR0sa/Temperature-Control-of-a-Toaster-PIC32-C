/* ************************************************************************** */
/** Descriptive File Name

  @Authors
 * Miguel Rosa     76655
 * Miguel COrreia  XXXXX 

  @Summary
 Connects the different actuators and acquisition circuits

  
 */
/* ************************************************************************** */

/* ************************************************************************** */
/* ************************************************************************** */
/* Section: Included Files                                                    */


#include "config_bits.h"

#include <xc.h>
#include <stdint.h>
#include <stdbool.h>
#include <sys/attribs.h>
#include "uart.h" 
#include <stdio.h>
#include <stdlib.h>

#include "init.h"
#include "deviceDrivers.h"


#define BMB 24833   
#define A0 9608  
#define S0 72544  
#define S1 71570 
#define UHIGH 99
#define ULOW   0
#define uc     10



char c[2];
int command=0;
static int pT100Voltage[2]={0,0};
int currentTemperature=0;
int controlSignal[2]={0,0};
int y[2]={0,0};
static uint32_t sample=0;
static uint32_t sample1=0;
void printAll(void);
int main(void)
{
     // Init UART and redirect tdin/stdot/stderr to UART
    TRISAbits.TRISA3 = 0;
    if(UartInit(PBCLOCK, 115200) != UART_SUCCESS) {
        PORTAbits.RA3 = 1; // If Led active error initializing UART
        while(1);
    }
    __XC_UART = 1; /* Redirect stdin/stdout/stderr to UART1*/
     
    //Init components
    initActuators();
    initADC();
    initTimer();
    initTimer1();
    initLeds();
    initOutputCompare();
    
    
    printf("Initialization Complete \r\n\n\n\n");
    
    command=getInt(c);
    printf("\n %d",command);
   
    
    
    while(1)
    {    
        if(flag_ADC)
        {  
          y[0]=y[1];
          pT100Voltage[1]=(ADC_value*3300)/1024;
          currentTemperature = readTemperature(pT100Voltage[1]);
          y[1]= currentTemperature;
          sample1++;
          
          flag_ADC=0;
        }    
        
        
        if(flag_T1)
        {    
            turnHeaterON(controlSignal[1]);
            flag_T1=0;
        }
        if(flag_T2)
        {
             start_ADC=1;
             
             
             
             /*RST Controller*/
              controlSignal[0]= controlSignal[1];
             
            
              controlSignal[1]=((BMB*(command*10000-command*A0))/(1000*10000))\
                             -((S0*y[1])/(100*1000)) \
                             +((S1*y[0])/(100*1000))  \
                             +controlSignal[0];
    
            /*Saturation*/
            if(controlSignal[1]>99)
            {
                controlSignal[1]=99;
            }    
            if(controlSignal[1]<0)
            {
                controlSignal[1]=0;
            }    
             
                        
						
			printAll();
			sample++;
            flag_T2=0;
        }
        
        
        
        
        
        
        
    }

}

void printAll(void)
{
    
            printf("input dutyCycle = %2d   Temperature = %4d Sample = %4d \r\n" \
                    ,controlSignal[1],y[1],sample);
            
        
}



    


