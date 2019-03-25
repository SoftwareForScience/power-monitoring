#!/bin/bash

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

