FROM resin/rpi-raspbian:latest

COPY ./metricbeat/ /usr/share/metricbeat

USER root
RUN chown -R root:root /usr/share/metricbeat

WORKDIR /usr/share/metricbeat

CMD ["/usr/share/metricbeat/metricbeat","-v","-e"]
