/**********************************************************************************************************************
* File Name    : readme.txt
* Description  : Contains general information about Example Project and detailed instructions
**********************************************************************************************************************/

1. Project Overview:

The example project demonstrate the timers and pwm mode.

2. Software Requirements:

Renesas Flexible Software Package (FSP): Version 1.0.0
e2 studio: Version 2025-10
GCC ARM Embedded Toolchain: Version 10.3.1.20210824
Terminal Console Application: Tera Term, RTT viewer or a similar application

3. Hardware Requirements:

Renesas RA6W1 Mother board.
Renesas RA6W2 Module.
Micro USB cable for programming and debugging or type C USB cable.
Connect P0_07(J201 pin 16) to Any LED in J611 LED TEST using jumper wire for checking PWM signal.

4. Verifying Operation:

1) Import the example project.
2) Generate, build the Example project.
3) use segger/RTTViewer for test and enable the 'ENABLE_UART_LOG' in uart_ep.h if needs for UART logs.
   Change input configuration(Menu->Input->Sending) to "Send on Enter".
4) Open a Teraterm UART console on the host PC to test and set correct COM port and baud rate to 115200.
5) Start a Debug session. This will automatically flash the image to the board.
6) After the debug session starts, click Run to execute the program (no need to press the board's reset button).
7) Enter each mode 1 or 2 or 3 to test periodic timer, pwm mode and one shot timer in Menu option and input the period or desired duty cycle. The one shot timer period is preset to 7000ms (in configuration.xml)
8) In case of periodic/one shot timer, the registered callback function will be excuted and show the log.

Note:
1) Segger RTT block address may be needed to download and observe EP operation using a hex file with RTT-Viewer.
   RTT Block address for hex file committed in repository are as follows:
   a. e2studio: 0x20003CD0
 
2) If an EP is modified, compiled, and downloaded please find the block address (for the variable in RAM called _SEGGER_RTT) 
   in .map file generated in the build configuration folder (Debug/Release).

3) The clock source is to set Xtal 32KHz by default and doesn't need to be changed.

Flashing Procedure:
1. Open e²studio and connect your JTAG debugger.
2. Go to Debug Configurations and select your .img.bin file in the Startup tab.
3. Start debugging and the image will be flashed automatically to the RA6W2.