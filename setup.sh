#!/bin/bash
sudo apt-get install
sudo apt-get -y dist-upgrade
sudo apt-get -y autoremove
sudo apt-get install python-pip

sudo chmod +x get-docker.sh
sudo ./get-docker.sh

sudo pip install docker
sudo pip install futures

sudo docker build -t twizzel/clustermd5sum .

sudo mkdir /etc/systemd/system/docker.service.d/
sudo cp override.conf /etc/systemd/system/docker.service.d/override.conf
sudo chown root:root /etc/systemd/system/docker.service.d/override.conf

sudo systemctl daemon-reload
sudo systemctl restart docker

echo "SETUP DONE! - Made by Twizzel"
