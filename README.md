# kbEmu

           Keyboard Emulator

kbEmu is a small program, installed on a Raspberry Pi Zero W, that emulates a keyboard.

It can be used to control a computer that, for instance, is in debug mode and you have to send complex strings to it (paswords, sets of commands, etc).
To do that, simply connect the raspberry Pi to the computer you want to control, using a USB cable, connect the controlling computer to the Raspberry Pi via WiFi and open a ssh session.
Run kbEmu in the terminal and the strings you type afterwards will be sent to the controlled computer. You can send sets of commands by copy-pasting them.
End the program by pressing Ctrl+C. Use "helpme" at the program prompt to display help information.

Installation (do it on an ordinary RaspberryPi):
Install RaspiOS on a SD card (RaspiOS Lite will be sufficient.) Make sure that ssh service can be used and that RaspiOS user and password are defined.
Boot from the SD card and connect to RaspiOS using ssh or connect to the Pi directly (keyboard + monitor).

Update the system and install git:<br/>
$ sudo apt update<br/>
$ sudo apt full-upgrade<br/>
$ sudo apt install git

Reboot if necessary, reconnect.

Clone the kbEmu folder on the Raspberry Pi.<br/>
$ git clone https://github.com/radmilofelix/kbEmu.git

Navigate to the kbEmu folder and run the install script:<br/>
$ cd ~/kbEmu<br/>
$ sudo ./install.sh

The install script will set the Raspberry Pi's own WiFi, define a keyboard device so that the Pi acts as a keyboard for the host to which it is connected with the USB cable, compile and install the program.

Default Wifi data:<br/>
SSID: kbEmu<br/>
Pass: kbEmuStart

Default IP to connect via SSH to the Raspberry Pi: 192.168.11.1

Move the SD to a Raspberry Pi Zero W. Connect to its WiFi network (kbEmu) and connect to it via SSH.

DHCP not working on Pi:
manually set the WiFi IP to 192.168.11.0 network.


Run kbEmu as root.
Enjoy.
