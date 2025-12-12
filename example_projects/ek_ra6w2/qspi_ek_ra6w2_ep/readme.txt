/**********************************************************************************************************************
* File Name    : readme.txt
* Description  : Contains general information about Example Project and detailed instructions
**********************************************************************************************************************/

1. Project Overview:

The example project demonstrates the typical use of the Flash QSPI APIs.
The project initializes the Flash QSPI and shows how to read/write.
The UART terminal Program (like Tera Term) can be used to get UART log.
The guide of input string values are displayed on the JLinkRTTViewer.
Any failure will also be displayed using JLinkRTTViewer.

2. Hardware and Software Requirements:

Two jumper wires are required to connect UART RX/TX.
QSPI interface is already connected inside the board in the EVK.
Renesas Flexible Software Package (FSP): Version 1.0.0
e2 studio: Version 2025-10
GCC ARM Embedded Toolchain: Version 10.3.1.20210824
Terminal Console Application: Tera Term, RTT viewer or a similar application

3. Hardware settings for the project:

Wiring details:

RA6W2-EK:
1) Connect UART0_RXD (Jumper J201 Pin 1) ----> P0_00 (Jumper J201 Pin 2)
2) Connect UART0_TXD (Jumper J201 Pin 3) ----> P0_01 (Jumper J201 Pin 4)
3) QSPI pins are connected already

4. Verifying Operation:

1) Import the Example project into e2 studio.
2) Build the project.
3) Start a Debug session. This will automatically flash the image to the board.
4) Open a Teraterm UART console on the host PC to test and set correct COM port and baud rate to 115200.
5) After the debug session starts, click Run to execute the program (no need to press the board's reset button).
6) Open a SEGGER RTT Viewer on the host PC to view the console output.
7) Check console log - "Data read matches with written data" will be printed out in successful case.

Note:
1) Segger RTT block address may be needed to download and observe EP operation using a hex file with RTT-Viewer.
   RTT Block address for hex file committed in repository are as follows:
   a. e2studio: 0x20003CD0
 
2) If an EP is modified, compiled, and downloaded please find the block address (for the variable in RAM called _SEGGER_RTT) 
   in .map file generated in the build configuration folder (Debug/Release).

Flashing Procedure:
1. Open e²studio and connect your JTAG debugger.
2. Go to Debug Configurations and select your .img.bin file in the Startup tab.
3. Start debugging and the image will be flashed automatically to the RA6W2.