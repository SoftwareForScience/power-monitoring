#!/bin/bash
sudo cp resolv.conf /etc/resolv.conf

# Update OS & Install pip (& git if init not run...)
sudo apt-get install
sudo apt-get -y dist-upgrade
sudo apt-get -y autoremove
sudo apt-get install -y git
sudo apt-get install -y python-pip

# Setup ssh-key
#sudo cp -r .ssh ~/.ssh
#sudo chown pi:pi -R ~/.ssh
#sudo chmod 700 -R ~/.ssh

# Install docker
sudo chmod +x get-docker.sh
sudo ./get-docker.sh

# Install python docker + futures
sudo pip install docker
sudo pip install futures

# Build Docker Image
sudo docker build -t twizzel/clustermd5sum docker-image

# Make Docker API public
sudo mkdir /etc/systemd/system/docker.service.d/
sudo cp override.conf /etc/systemd/system/docker.service.d/override.conf
sudo chown root:root /etc/systemd/system/docker.service.d/override.conf

# Reload Docker Daemon
sudo systemctl daemon-reload
sudo systemctl restart docker

# Yeahhh... Some sneaky reference ;-)
echo "SETUP DONE! - Made by Twizzel"

