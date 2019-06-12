FROM python:3.6-slim-stretch
MAINTAINER Tom Buskens <t.buskens@twizzel.net>
RUN apt-get update -y
RUN apt-get install -y python3 python-pip-whl python3-pip


COPY data /app
WORKDIR /app
RUN pip3 install -r requirements.txt

#RUN python3 ./setup.py

EXPOSE 9090
ENTRYPOINT ["python3"]
CMD ["run-production.py"]