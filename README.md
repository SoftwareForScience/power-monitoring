# Metricbeat/prometheus docker-compose file
To run this compose file you have to prepare a few things.

1. Run the Ansible (see Ansible repository) script to install docker and docker-compose.
2. Setup the ELK-stack (see ELK-stack repository).
3. Set a few things in config/metricbeat.yml with the settings provided in the ELK-stack. **When you don't have a license, you don't have a username/password login. This is not save so don't make your stack public!**
```
output.elasticsearch:
  hosts: ['elastic.twizzel.net:443']
  username: elastic
  password: "XCTOP/16fcBeW9M3Il5E4g=="
```
and
```
setup.kibana:
  host: "kibana.twizzel.net:443"
  username: elastic
  password: "XCTOP/16fcBeW9M3Il5E4g=="
```