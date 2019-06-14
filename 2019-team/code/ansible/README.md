#Ansible Playbook
##Install necessary software packages
Clone and navigate to the Ansible folder. To the `inventory` file, add all the ip's of the pi's that need to be installed. Do this in this format: `rpi04 ansible_ssh_host=1.1.1.1`. When this is done, execute the playbook.
```
ansible-playbook -i inventory -l cluster install.yaml
-i = inventory tag
-l = target group in the inventory file
```
