#!/usr/bin/env python

from __future__ import division
from prometheus_client import start_http_server, Summary, Gauge

from ina219 import INA219, DeviceRangeError
from subprocess import PIPE, Popen
import psutil

from .prometheus_filter import Filtervalue

#-------------------------------------------------------------------
# Willen we hier nog naar kijken of niet???

#def get_cpu_temperature():
#    process = Popen(['vcgencmd', 'measure_temp'], stdout=PIPE)
#    output, _error = process.communicate()
#    return float(output[output.index('=') + 1:output.rindex("'")])
#-------------------------------------------------------------------


#-------------------------------------------------------------------
# 
# multithreading for filtering and posting
# 
# 
#-------------------------------------------------------------------

collect_time = 1


inamodule = INA219(0.1, 2.0)
inamodule.configure(ina.RANGE_16V, GAIN_8_320MV, ADC_12BIT, ADC_12BIT)


REQUEST_TIME = Summary('request_processing_seconds',
                       'Time spent processing request')

prometheus_current = Gauge('energy_current', 'Filtered current of the system')
prometheus_voltage = Gauge('energy_voltage', 'Filtered voltage of the system')
prometheus_power = Gauge('energy_power', 'Filtered power of the system')


filtered_current = Filtervalue(inamodule.current())
filtered_voltage = Filtervalue(inamodule.voltage() * 1000)
filtered_power = 0.0


if __name__ == '__main__':
	# Start server for Prometheus to listen to
	start_http_server(8000)
	
	while True:
		
		# Filter every /interval/ time
		start_time = time.time()
		while time.time() < start_time + collect_time:
			filtered_current.updatevalue(inamodule.current()       , 0.1)
			filtered_voltage.updatevalue(inamodule.voltage() * 1000, 0.1)
		
		filtered_power = current.averagevalue * voltage.averagevalue / 1000
		
		# post metrics
		prometheus_current.set(filtered_current)
		prometheus_voltage.set(filtered_voltage)
		prometheus_power.set(filtered_power)