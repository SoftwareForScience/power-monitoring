#!/bin/bash

# Change user to pi
# (already pi, but to be sure, nothing harmfull...
# Don't ask, don't say anything, just run this file idiot!)
sudo chown pi:pi -R ../.ssh
sudo chown pi:pi -R ../docker-cluster
git pull origin master

# Now we gonna setup something...
echo "We are going to run setup.sh"
echo "In the meantime you can listen to some music..."
echo "Listen for example to: 'https://www.youtube.com/watch?v=B1qWnmycriA'
echo "CLICK FAST! Starting in 7 seconds..."

sleep 7

# Run setup.sh..
./setup.sh

# Bye Bye!!
