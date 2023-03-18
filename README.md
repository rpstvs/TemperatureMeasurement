##Temperature Measurement with 8051 Microcontroller


### Tools Used
**Microcontroller:** 8051F340

**Temperature Sensor:** MCP9700

**Display:** 16x2 LCD

**IDE:** MCU8051


# Run Down

The Microcontroller is configured to measure the voltage of the sensor at P3.4 - (This pin is made as an Analog Input).

The value measured in the pin is converted from an analog value to digital, through an Analog to Digital converter (ADC) - a feature from the 8051f340.

After converting the value, a second conversion is made to get the value in ºC and then is pushed to an LCD as an ASCII value.

