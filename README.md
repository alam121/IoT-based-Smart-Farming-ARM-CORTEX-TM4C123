# IoT-based-Smart-Farming-ARM-CORTEX-TM4C123

Project based on Arm contex Tiva lanuchpad TM4C123GH6PM

The project includes:
* implementation of adc header file (For Photo Diode)
* implementation of uart header file
* implementation header for TM4C123 GPIO header file
* main.c ( implementation of sensor interface (DHT-11, Soil Moisture SKN, PhotoDiode) 


![alt text](https://github.com/alam121/IoT-based-Smart-Farming-ARM-CORTEX-TM4C123/blob/master/1.JPG)



## Components required 

* Tiva launchpad TM4C123G56PM
* DHT-11 
* Photodiode
* SKN Soil moisture sensor
* 16x2 LCD



A. Tiva Launchpad:

The Tiva Launchpad (TM4C123GH6PM) was used as the microcontroller in the project. The microcontroller has a 64 pin package. Out of these 64 pins, 43 pins are available for the purpose of GPIO pins. These GPIO pins are grouped into six ports labelled Port A to Port F. Port A to D are 8 pin ports, while port E is 6 pin and Port F is 5 pin. Each of the pins on these ports can be configured as GPIO. Some of the port pins also have special peripheral functionalities multiplexed along with GPIO functionality and can be configured for that purpose as well.



B. DHT 22 humidity and temperature sensor:

1. Features: DHT 22 is a Digital Humidity and Temperature sensor which gives a precise value of both temperature and humidity measurement. It utilizes exclusive digital-signal-collecting- technique and humidity sensing technology, assuring its reliability and stability. No extra components are required for its interfacing with the microcontroller. Small size & low consumption & long transmission distance (20m) enable DHT22 to be suited in all kinds of harsh application occasions. Single-row packaged with four pins, making the connection very convenient. Its humidity measurement range is 0 to 100% RH (Relative Humidity) and temperature range is -40 to 80 degree Celsius.

2. Power and Pins:Power's voltage should be 3.3-6V DC. When power is supplied to sensor, don't send any instruction to the sensor within one second to pass unstable status. One capacitor valued 100nF can be added between VDD and GND for wave filtering.

3. Communication and signal: Single-bus data is used for communication between MCU and DHT22, it costs 5mS for single time communication. Data is comprised of integral and decimal part, the following is the formula for data. DHT22 send out higher data bit firstly! DATA=8 bit integral RH data+8 bit decimal RH data+8 bit integral T data+8 bit decimal T data+8 bit check-sum If the data transmission is right, check-sum should be the last 8 bit of "8 bit integral RH data+8 bit decimal RH data+8 bit integral T data+8 bit decimal T data". Figure 3. Serial data transfer between DHT 22 and Microcontroller. As shown in Figure 2, when MCU send start signal, DHT22 change from low-power- consumption-mode to running-mode. When MCU finishes sending the start signal, DHT22 will send response signal of 40-bit data that reflect the relative humidity and temperature information to MCU. Without start signal from MCU, DHT22 will not give response signal to MCU. One start signal for one time's response data that reflect the relative humidity and temperature information from DHT22. DHT22 will change to low- power-consumption-mode when data collecting finish if it don't receive start signal from MCU again.

C. Light Intensity Sensor (Photodiode):

Photodiode is designed to be responsive to optical input in such a way that when light falls on it, a reverse current flows through it due to the principle of photoelectric effect. As a result, a potential is developed across it. The reverse photoelectric current varies directly with the intensity of light.

Greater the current, greater will be the current and so the voltage. So, by measuring the voltage developed across the photodiode, we can calculate the intensity of light by multiplying the voltage by a suitable constant factor.

D. 16 × 2 LCD Display:


A liquid-crystal display (LCD) is a flat-panel display or other electronically modulated optical device that uses the light-modulating properties of liquid crystals. Liquid crystals do not emit light directly, instead using a backlight or reflector to produce images in color or monochrome.LCDs are used in a wide range of applications including computer monitors, televisions, instrument panels, aircraft cockpit displays, and indoor and outdoor signage. Small LCD screens are common in portable consumer devices such as digital cameras, watches, calculators, and mobile telephones, including smartphones. LCD screens are available in a wider range of screen sizes than CRT and plasma displays, with LCD screens available in sizes ranging from tiny digital watches to huge, big-screen television sets. 16×2 LCD is named so because it has 16 Columns and 2 Rows.
