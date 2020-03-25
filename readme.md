<div id="readme" class="Box-body readme blob js-code-block-container">
 <article class="markdown-body entry-content p-3 p-md-6" itemprop="text"><p><a href="https://www.microchip.com" rel="nofollow"><img src="images/MicrochipLogo.png" alt="MCHP" style="max-width:100%;"></a></p>

# PIC18F47Q10 EUSART Sending "Hello World" message

## Objective:

This example shows how to send a string message from the PIC18F47Q10 microcontroller to the PC and use MPLAB Data Visualizer Terminal to see it.

## Resources:

- Technical Brief Link [(linkTBD)](http://www.microchip.com/)
- MPLAB® X IDE 5.30 or newer [(microchip.com/mplab/mplab-x-ide)](http://www.microchip.com/mplab/mplab-x-ide)
- MPLAB® XC8 2.10 or newer compiler [(microchip.com/mplab/compilers)](http://www.microchip.com/mplab/compilers)
- PIC18F47Q10 Curiosity Nano [(DM182029)](https://www.microchip.com/Developmenttools/ProductDetails/DM182029)
- [PIC18F47Q10 datasheet](http://ww1.microchip.com/downloads/en/DeviceDoc/40002043D.pdf) for more information or specifications.

## Hardware Configuration:

The PIC18F47Q10 Curiosity Nano Development Board [(DM182029)](https://www.microchip.com/Developmenttools/ProductDetails/DM182029) is used as the test platform. It has an onboard debugger that acts as an USART to USB convertor so no further hardware is needed.

The following configurations must be made for this project:

- RD0 pin - Configured as digital output

## Demo:

Run the code, start MPLAB® X Data Visualizer on the correct COM port and select the terminal input source than messages will start appearing.

<img src="images/demo.png" alt="Demo in MPLABX Data Visualizer"/>
