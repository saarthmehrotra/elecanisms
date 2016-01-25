blink
======
Guide to making two LEDs blink on a pic.


In order to get code working on our pic that can make two LEDs alternate
blinking, first you should get the your development environment set up and working. We were working in Linux so that is the system for which this guide will be written. The first stages involve getting the correct compilers from http://www.microchip.com/compilers. You must download and install MPLABAX XC16 Compiler v1.25. We ran into some trouble using the installer and had to run the install in text mode for some of our computers. You may also want to change the permissions from the executable to be an executable rather than only a readable file. Then you can get scons working by running sudo apt-get install scons on the terminal. You then get MPLABX from http://www.microchip.com/mplabide and install it. Next you have to get pyusb and usblib. You can google each of these libraries find the .tar and install them. 

You can also get some base code for working on the pic boards by using the elecanisms git repository. Git fork and clone the repository https://github.com/OlinElecanisms/elecanisms. In this repository, go into the blink folder and edited the code in blink.c to make another LED blink when the first LED is not blinking. Here is the relevant code.

    led_on(&led1);
    led_off(&led2);						//change #1
    timer_setPeriod(&timer2, 0.5);
    timer_start(&timer2);

    while (1) {
        if (timer_flag(&timer2)) {
            timer_lower(&timer2);
            led_toggle(&led1);
            led_toggle(&led2);			//change #2
        }


You also need to change a line in SConstruct that says this
	env.PrependENVPath('PATH', '/Applications/microchip/xc16/v1.25/bin')
to this
	env.PrependENVPath('PATH', '/opt/microchip/xc16/v1.25/bin').
This changes the path for the compiler to point in the right place.
Next you go back in to the terminal in the blink folder and run scons. If no errors are printed, you have probably installed everything correctly. 

Next you can get this running on the pic. First plug in your pic to your computer. Put your pic into bootloader mode by holding down the black button in the corner next to the usb adapter as you press the red button adjacent to it. Next go to the site_scons folder in the repository. Run pythonbootloadergui.py and a gui should open up. You may get a permissions error. Make sure to run this command as a superuser. Make sure it says you are connected to a pic. In the top write corner there is a file menu in which there is an option to import a hex file. Select that and browse to the blink folder in the pop-up. Select the blink hex file and open it. Then hit the button that says write. After the file is written, select disconnect and run. Congratulations! you should have blinking lights on your pic. 