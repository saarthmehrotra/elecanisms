READ ME by SAARTH 

Installing Software on Ubuntu 14.04

1. Install Micro Chip Compiler http://www.microchip.com/compilers /opt/microchip/xc16/v1.23/bin
Note: To be able to run 32 programs http://askubuntu.com/questions/297151/how-to-run-32-bit-programs-on-a-64-bit-system
2. Install SCONS
 $ sudo apt-get install scons
3. Install MPLABX
http://www.microchip.com/mplabide
4. Install USB Stuff
http://www.libusb.org/
https://walac.github.io/pyusb/

Compiling and Uploading Code

1. Clone elecanism directory 
1.5 Put board in bootloader mode by holding down the reset and 
2. Make changes to the .c file
3. Run "scons" in the directory of .c file to make .hex file
4. Run bootloader.py from site_scons directory
5. Click on file and select the compiled .hex file
6. Write file
7. Click Disconnect/Run




