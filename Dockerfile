FROM resin/rpi-raspbian:latest

COPY metricbeat /metricbeat

CMD ["./metricbeat","-v","-e"]
