#!/bin/bash

# DNS fix (Yes this is already in init.sh, but I DONT CARE,
# this is for people who run this standalone ;-] )
sudo cp dhcpcd.conf /etc/dhcpcd.conf
sudo chmod 664 /etc/dhcpcd.conf
sudo chown root:netdev /etc/dhcpcd.conf
sudo service dhcpcd restart


# Update OS & Install pip (& git if init not run...)
sudo apt-get update
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
sudo mkdir /etc/systemd/system/docker.service.d
sudo chown -R root:root /etc/systemd/system/docker.service.d
sudo chmod 755 /etc/systemd/system/docker.service.d
sudo cp remote-api.conf /etc/systemd/system/docker.service.d/remote-api.conf
sudo chmod 644 /etc/systemd/system/docker.service.d/remote-api.conf

# Reload Docker Daemon
sudo systemctl daemon-reload
sudo systemctl restart docker

# Swarm Setup
docker swarm join --token SWMTKN-1-2ykeifmtnzicmpt0cc4ly5bfxwum1sxigb8mag163dc5iq21as-3jk1ict0xj6h2b1bnne48s78i 192.168.1.15:2377

# Yeahhh... Some sneaky reference ;-)
echo "SETUP DONE! - Made by Twizzel"

