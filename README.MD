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

- #### 8086 microprocessor interfacing circuit to demultiplex address and data lines ####
![8086_interfacing](./Images/8086_interfacing.png)
    - __8086 microprocessor__
    ![8086_mup](./Images/8086_mup.png)
    - __74LS373 (Octal Latch) for Address de-multiplexing__
    ![74LS373](./Images/74LS373.png)
    - __74LS245 (8 bit bi-directional buffer) for Data de-multiplexing__
    ![74LS245](./Images/74LS245.png)

- #### Memory Interfacing along with peripheral I/O Interfacing ####
![memory_interfacing](./Images/memory_interfacing.png)
    - __ROM and RAM chip select decoding logic__
    ![memory_decoding](./Images/memory_decoding.png)
    - __READ and WRITE Enable for EVEN and ODD Banks of ROM and RAM__
    ![even_odd_bank_select](./Images/even_odd_bank_select.png)
    - __4k ROM chip (2732)__
    ![4k_rom](./Images/4k_rom.png)
    - __2k RAM chip (6116)__
    ![2k_ram](./Images/2k_ram.png)
    - __IOR and IOW signals__
    ![ior_iow](./Images/ior_iow.png)
    - __8255 chip select logic (base address of 8255 = 00H)__
    ![8255_cs](./Images/8255_cs.png)

- #### 8255 PPI, Humidity output signal processing and LCD display ####
![lcd_display](./Images/lcd_display.png)
    - __8255A chip interfacing__
    ![8255_interfacing](./Images/8255_interfacing.png)
    - __Humidity sensor modelled as a VCCS (Voltage Controlled Current Source) along with a potentiometer to change output current__
    ![humidity_sensor_model](./Images/humidity_sensor_model.png)
    - __ADC chip interfacing__
    ![adc_interfacing](./Images/adc_interfacing.png)
    - __LCD Output Display__
    ![lcd_output](./Images/lcd_output.png)
    