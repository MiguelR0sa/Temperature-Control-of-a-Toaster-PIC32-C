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

#ifndef DEVICEDRIVERS_H    /* Guard against multiple inclusion */
#define DEVICEDRIVERS_H

#include <stdint.h>

/*Function prototypes*/
void turnHeaterON(uint8_t power);
uint32_t readTemperature( uint32_t pT100Voltage);
void turnFanON(uint8_t power); 

#define UPPER_VALUE       3000 //upper value of the input signal in mv
#define ZERO_MARGIN       100  //margin in mv for zero cross detection
#define ACQUSITION_OFFSET 650  // acquisition ciruit offset
#define TV_RATIO          27200   //temperatureVariation/voltagVaritaion=21.739 ratio *1000  float

#endif /* _EXAMPLE_FILE_NAME_H */

