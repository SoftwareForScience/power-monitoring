#!/usr/bin/env python

from __future__ import division
from prometheus_client import start_http_server, Summary, Gauge

from ina219 import INA219, DeviceRangeError
from subprocess import PIPE, Popen
import random
import time
import psutil
import matplotlib.pyplot as plt

SHUNT_OHMS = 0.1
MAX_EXPECTED_AMPS = 2.0
ina = INA219(SHUNT_OHMS, MAX_EXPECTED_AMPS)
ina.configure(ina.RANGE_16V)

REQUEST_TIME = Summary('request_processing_seconds',
                       'Time spent processing request')
g1 = Gauge('Power_usage', 'Description of gauge')
g1.set(ina.power())

g2 = Gauge('Voltage', 'Description of gauge')
g2.set(abs(ina.current()))


#def get_cpu_temperature():
#    process = Popen(['vcgencmd', 'measure_temp'], stdout=PIPE)
#    output, _error = process.communicate()
#    return float(output[output.index('=') + 1:output.rindex("'")])


#g3 = Gauge('Temperature', 'Description of gauge')
#g3.set(get_cpu_temperature())


# Decorate function with metric.
@REQUEST_TIME.time()
def process_request(t):
    """A dummy function that takes some time."""
    time.sleep(t)


if __name__ == '__main__':
    # Start up the server to expose the metrics.
    start_http_server(8000)
    # Generate some requests.
    while True:
        process_request(random.random())
        g1.set(ina.power())
        g2.set(abs(ina.current()))
#        g3.set(get_cpu_temperature())
