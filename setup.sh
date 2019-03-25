#!/bin/bash

# DNS fix (Yes this is already in init.sh, but I DONT CARE,
# this is for people who run this standalone ;-] )
sudo cp dhcpcd.conf /etc/dhcpcd.conf
sudo chmod 664 /etc/dhcpcd.conf
sudo chown root:netdev /etc/dhcpcd.conf
sudo service dhcpcd restart


# Update OS & Install pip (& git if init not run...)
sudo apt-get install
sudo apt-get -y dist-upgrade
sudo apt-get -y autoremove
sudo apt-get install -y git
sudo apt-get install -y python-pip

# Reboot now...
echo "REBOOT THIS THING! (test)"

