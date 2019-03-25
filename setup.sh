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

# Install docker
sudo chmod +x get-docker.sh
sudo ./get-docker.sh

# Install python docker + futures
sudo pip install docker
sudo pip install futures

# Build Docker Image
sudo docker build -t twizzel/clustermd5sum docker-image

# Make Docker API public
#sudo mkdir /etc/systemd/system/docker.service.d/
#sudo cp override.conf /etc/systemd/system/docker.service.d/override.conf
#sudo chown root:root /etc/systemd/system/docker.service.d/override.conf

# Reload Docker Daemon
sudo systemctl daemon-reload
sudo systemctl restart docker

# Yeahhh... Some sneaky reference ;-)
echo "SETUP DONE! - Made by Twizzel"

