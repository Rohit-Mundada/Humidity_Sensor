# Modelling of 2D-Material based Humidity Sensor - Development of circuit to drive the Humidity Sensor #

## VLSI Design/Circuit Design ##

This project is focused on displaying the humidity value in ppm (parts per million) from a humidity sensor. The humidity sensor outputs current in micro Amperes and this has to be converted into appropriate ppm values assuming a linear function between current and humidity.

Current (micro A) | Humidity (ppm)
| :---: | :---: |
 0 | 0
 105 | 5.6

The circuit was designed in __Proteus 7 Professional__ and the code was written in __Assembly Language__. The code was comipled into an executable file via __EMU 8086__ application. The executable file was loaded into the design and the simulation was run.

Below are some of the screen shots of the circuit designed and the humidity output.

- - - -

1. 8086 microprocessor interfacing circuit to demultiplex address and data lines
![8086_interfacing](./Images/8086_interfacing.png)
    1. 8086 microprocessor
    ![8086_mup](8086_mup.png)
    2. 74LS373 (Octal Latch) for Address de-multiplexing
    ![74LS373](74LS373.png)
    3. 74LS245 (8 bit bi-directional buffer) for Data de-multiplexing
    ![74LS245](74LS245.png)

