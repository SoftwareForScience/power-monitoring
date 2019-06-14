#!/usr/bin/env python
from ina219 import INA219
from ina219 import DeviceRangeError
# Import Elasticsearch package 
from elasticsearch import Elasticsearch 
# Connect to the elastic cluster


es=Elasticsearch([{'host':'207.180.205.115','port':9200}])
es


SHUNT_OHMS = 0.1


def read():
    ina = INA219(SHUNT_OHMS)
    ina.configure()

    print("Bus Voltage: %.3f V" % ina.voltage())
    try:
        e1={
            "Voltage": ina.voltage(),
            "Current": ina.current(),
            "Power": ina.power()
        }
        print e1
	res = es.index(index='powerReadings',doc_type='pi1',id=1,body=e1)
    except DeviceRangeError as e:
        # Current out of device range with specified shunt resister
        print(e)


if __name__ == "__main__":
    read()
