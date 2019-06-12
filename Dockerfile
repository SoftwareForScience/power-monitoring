#FROM resin/rpi-raspbian:latest
FROM arm32v7/python:3.6-slim-stretch

MAINTAINER Tom Buskens <t.buskens@twizzel.net>
RUN apt-get update -y
RUN apt-get install -y python3 python-pip-whl python3-pip python3-matplotlib 


COPY data /app
COPY requirements.txt /app/requirements.txt
WORKDIR /app

RUN python3 --version

RUN pip3 install -r requirements.txt

EXPOSE 9090
ENTRYPOINT ["python3"]
CMD ["metric_ina.py"]
