# kbEmu
 Keyboard Emulator
kbEmu is a small program, installed on a Raspberry Pi Zero W, that emulates a keyboard.

It can be used to control a computer that, for instance, is in debug mode and you have to send complex strings to it (paswords, sets of commands, etc).
To do that, simply connect the raspberry Pi to the computer you want to control, using a USB cable, connect the controlling computer to the Raspberry Pi via WiFi and open a ssh session.
Run kbEmu in the terminal and the strings you type afterwards will be sent to the controlled computer. You can send sets of commands by copy-pasting them set.
End the program by pressing Ctrl+C. Use "helpme" at the program prompt to display help information.

Default WifiData:
SSID: kbEmu
Pass: kbEmuStart

Default IP to connect to the Raspberry Pi: 192.168.11.1

Installation (ordinary RaspberryPi):
Install RaspiOS on a SD card (RaspiOS Lie will be sufficient.) Make sure that ssh service can be used and that RaspiOS user and password are defined.
Boot from the SD card and connect to RaspiOS using ssh.

Update the system:

$ sudo apt update

$ sudo apt full-upgrade

Reboot, reconnect.

Copy the kbEmu folder on the Raspberry Pi. Navigate to the folder, and make the install script executable:

$ cd ~/kbEmu

$ chmod +x install.sh

Run the install script:

$ sudo ./install.sh

Move the SD to a Raspberry Pi Zero w. Connect to its WiFi network (kbEmu).
Run kbEmu as root.
Enjoy.
