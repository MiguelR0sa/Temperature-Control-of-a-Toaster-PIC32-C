/* ************************************************************************** */
/** Descriptive File Name

  

  @Summary
    -> Implementation of the toaster actuator
    -> COnverts acquisition circuit output value into temperature
 
 */

#include "deviceDrivers.h"
#include "init.h"


#include <xc.h>
#include <stdint.h>
#include <stdbool.h>
#include <sys/attribs.h>
#include <stdio.h>
#include <stdlib.h>

/*
 Description: Turn on the heater with wanted power ,0-100% 
 */
static uint8_t counter=0;
void turnHeaterON(uint8_t power)
{
    
   if(ZERO_CROSS==1)
   { 
     
       counter=0;
       ACTUATOR=LOW;
   }
   if((counter>=(100-power)) && (power>0))
   {    
     
       ACTUATOR=HIGH;
   }    
   counter++;
   



}
void turnFanON(uint8_t power)  
{
 
    OC1RS=PR3*power/100;



}
/*Converts acquisition circuit output value into temperature*/
uint32_t readTemperature( uint32_t pT100Voltage)
{
    if(pT100Voltage>ACQUSITION_OFFSET)
    return ((TV_RATIO*(pT100Voltage-ACQUSITION_OFFSET))/10000)+3000;     
    else return 0; //Temperature below 50

}


