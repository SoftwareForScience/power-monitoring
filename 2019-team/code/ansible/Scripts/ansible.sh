#!/bin/bash

# Upgrade packages
sudo apt-get update
sudo apt-get dist-upgrade -y
sudo apt-get autoremove -y

# Git & PIP
sudo apt-get install -y git
sudo apt-get install -y python-pip
sudo apt-get install -y python-dev
sudo apt-get install -y libssl-dev

# Docker-Compose
sudo apt-get install libffi-dev
sudo pip install docker-compose

# Install Docker
wget https://get.docker.com/ --output-document get-docker.sh
sudo chmod +x get-docker.sh
sudo ./get-docker.sh
