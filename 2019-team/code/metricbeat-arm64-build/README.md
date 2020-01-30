# Prometheus Build
This image provides all the tools needed in the Dockerfile to run metricbeats on an Raspberry Pi.

**If you want to push the images to registry.twizzel.net, please create an account at https://gitlab.twizzel.net and ask Tom Buskens (t.buskens@twizzel.net) for access**

## Build and push this image.
Follow this tutorial: [build-a-docker-image-and-push-it-to-docker-hub](http://blog.shippable.com/build-a-docker-image-and-push-it-to-docker-hub)

## Example
```bash
docker login registry.twizzel.net
docker build -t registry.twizzel.net/hva/sfs-power-monitoring/metricbeat-arm64-build .
docker push registry.twizzel.net/hva/sfs-power-monitoring/metricbeat-arm64-build:v0.3
```