# Temperature-Control-of-a-Toaster-PIC32-C

This work was part of an instrumentation project aiming for the temperature control of a toaster.
Temperature measurements were achieved with an RTD for which, a signal conditioning circuit was developed. 
In order to heat the toaster an actuator had to be interfaced though phase control.

These modules were connected to a PIC32 harbouring an RST controller to force the temperature into a desired setpoint.
The C code for the PIC32 microcontroller is shown in the repository, which also includes device drivers for the mentioned modules.
