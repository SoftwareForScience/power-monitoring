#Ansible Playbook

This README will provide all the necessary steps to install and use Ansible

##Prerequisites

For Ansible to work, you'll need a host PC and some slaves to execute the Ansible scripts to. The host and slaves need to be accessible by SSH. This can be done by either connecting the systems to the same network using a switch and ethernet cables or a wifi network. The slaves also need to be added to your `~/.ssh/know_hosts` file. use [this](https://oit.colorado.edu/change-host-keys) guide to find out how to do that. This can also be easily be achieved by first connecting to each slave before executing the Ansible script.

##Install necessary software packages

To use Ansible, you first have to install Ansible by executing `sudo apt install ansible`. Check if Ansible is installed with `ansible --version`, the version installed has to be greater than 2.5.

##Execute the Ansible Playbook

Clone this repository and navigate to the repository's folder. To the `inventory` file, add all the ip's of the pi's that need to be installed. Do this in this format: `rpi04 ansible_ssh_host=1.1.1.1`, as shown in the `inventory.example` file. When this is done, execute the playbook using the command below.
```
ansible-playbook -i inventory -l cluster install.yaml
-i = inventory tag
-l = target group in the inventory file
```
**Note:** This may take a while when done on a slower system like a Raspberry Pi since it has fewer resources to work with for compiling the Python Libraries. Don't cancel any tasks, even if they take longer than half an hour.
