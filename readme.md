## NXP LPC-54608 USB Bootloader Project

Architecture 

![Memory Architecture](img/memory.png)

![Connection](img/connection.png)

Place your application binary in the pen drive under a filename "APP.BIN" in the root directory.

You must be able to see the contents printed in Debug console configured at 115200 Baud Rate.

To Do:

Check the file: penDrive.c, 

As soon as APP.BIN is detected in the pen drive,
1. App Region Flash is erased.
2. Read from pen drive as 128 Bytes chunk happens.
3. This is printed in your terminal.
4. TBD: Write the packets in Flash (refer to elico UART Bootloader example previously shared.)
5. TBD: Complete the Boot Jump logic.

