#! /bin/bash

apt install -y hostapd dnsmasq
systemctl unmask hostapd
systemctl enable hostapd

DEBIAN_FRONTEND=noninteractive apt install -y netfilter-persistent iptables-persistent

cp /etc/dhcpcd.conf /etc/dhcpd.conf.old
echo "" >> /etc/dhcpcd.conf
echo "interface wlan0" >> /etc/dhcpcd.conf
echo "    static ip_address=192.168.11.1/24" >> /etc/dhcpcd.conf
echo "    nohook wpa_supplicant" >> /etc/dhcpcd.conf

mv /etc/dnsmasq.conf /etc/dnsmasq.conf.orig
echo "" >> /etc/dnsmasq.conf
echo "interface=wlan0 # Listening interface" >> /etc/dnsmasq.conf
echo "dhcp-range=192.168.11.2,192.168.11.20,255.255.255.0,24h" >> /etc/dnsmasq.conf
echo "                # Pool of IP addresses served via DHCP" >> /etc/dnsmasq.conf

cp config/routed-ap.conf /etc/sysctl.dhcpd
rfkill unblock wlan
cp config/hostapd.conf /etc/hostapd

cp /etc/rc.local /etc/rc.local.old
cp scripts/rc.local /etc
chmod +x /etc/rc.local

echo "dtoverlay=dwc2" | sudo tee -a /boot/config.txt
echo "dwc2" | sudo tee -a /etc/modules
echo "libcomposite" | sudo tee -a /etc/modules

cp scripts/isticktoit_usb /usr/bin
chmod +x /usr/bin/isticktoit_usb

make clean
make
make install
make clean
echo
echo

echo "Installation finished."
echo "Usage: $ sudo kbEmu"


