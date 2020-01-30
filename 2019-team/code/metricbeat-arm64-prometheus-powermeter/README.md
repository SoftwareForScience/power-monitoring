# UPDATE 18-06-2019
The two custom images of registry.twizzel.net will remain available.

If you want to use your own registry or the docker-hub, use the ' - build' repositories to build, create and push your image.


# Metricbeat/prometheus docker-compose file
To run this compose file you have to prepare a few things.

1. Run the Ansible (see Ansible repository) script to install docker, docker-compose and to enable the I2C device.
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
4. After all this steps your prometheus/metricbeats stack is ready and will send data to your ELK-stack. If you want to test this, you can follow the tutorial on kibana (<kibana_host>/app/kibana#/home/tutorial/prometheusMetrics?_g=())


## Tools to check and use
For docker and docker-compose commands you need sudo! (or you have to be in the 'docker' group)

### Show logs
```bash
docker-compose logs -f metricbeat
docker-compose logs -f prometheus
```

### Start | Stop | Kill | Restart
```bash
docker-compose up -d
docker-compose stop
docker-compose kill
docker-compose restart
```

