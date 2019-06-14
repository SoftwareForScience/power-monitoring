#!/usr/bin/env python

from __future__ import division
from prometheus_client import start_http_server, Summary, Gauge
from time import sleep

from ina219 import INA219, DeviceRangeError
from subprocess import PIPE, Popen
import psutil
import time



class Filtervalue:
	def __init__(self, initialvalue):
		self.averagevalue = initialvalue
	
	# def __init__(self, initialvalue, sumcount):
		# self.sumcount = sumcount
		# self.lastvalues = []
		
		# for x in range(0, self.sumcount+1):		#0-100
			# self.lastvalues[x] = self.averagevalue
		
	
	def updatevalue(self, newvalue, avgweight):		# three different types of filter
		# sumofvalues = 0
		
		# self.lastvalues[self.sumcount] = self.newvalue	#100
		
		# for x in range(0, self.sumcount):		#0-99
			# self.lastvalues[x] = self.lastvalues[x+1]
			# sumofvalues += self.lastvalues[x]
		
		# self.averagevalue = sumofvalues / self.sumcount
		
		# self.lastvalues[sumcount] = ((sumofvalues * (1-avgweight)) + (self.newvalue * (avgweight))) / sumcount		#extra filtering
		
		self.averagevalue = (self.averagevalue * (1-avgweight)) + (newvalue * avgweight)

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
inamodule.configure(inamodule.RANGE_16V, inamodule.GAIN_8_320MV, inamodule.ADC_12BIT, inamodule.ADC_12BIT)


REQUEST_TIME = Summary('request_processing_seconds',
                       'Time spent processing request')

prometheus_current = Gauge('energy_current', 'Filtered current of the system')
prometheus_voltage = Gauge('energy_voltage', 'Filtered voltage of the system')
prometheus_power = Gauge('energy_power', 'Filtered power of the system')

prometheus_cpu_percent = Gauge('cpu_percent', 'Filtered CPU percentage')
prometheus_memory_mb = Gauge('memory_mb', 'Filtered RAM consumption')


#initialize variables with Filtervalue constructor
filtered_current = Filtervalue(inamodule.current())
filtered_voltage = Filtervalue(inamodule.voltage() * 1000)
filtered_power = 0.0

filtered_cpu_percent = Filtervalue(psutil.cpu_percent())
filtered_memory_mb = Filtervalue(0.0)


if __name__ == '__main__':
	# Start server for Prometheus to scrape from
	start_http_server(9090)

	while True:

		print("Voltage: %.3f V  Current: %.3f mA  Power: %.3f mw" % (inamodule.voltage(), inamodule.current(), inamodule.power()))

		# Filter every /interval/ time
		start_time = time.time()
		while time.time() < start_time + collect_time:
			filtered_current.updatevalue(inamodule.current()	       , 0.1)
			filtered_voltage.updatevalue(inamodule.voltage() * 1000, 0.1)

			filtered_cpu_percent.updatevalue(psutil.cpu_percent(), 0.1)
			ram = psutil.virtual_memory()
			filtered_memory_mb.updatevalue(ram.used / 1048576, 0.1)		# b to mb

		filtered_power = filtered_current.averagevalue * filtered_voltage.averagevalue / 1000

		# post metrics
		prometheus_current.set(filtered_current.averagevalue)
		prometheus_voltage.set(filtered_voltage.averagevalue)
		prometheus_power.set(filtered_power)

		prometheus_cpu_percent.set(filtered_cpu_percent.averagevalue)
		prometheus_memory_mb.set(filtered_memory_mb.averagevalue)
		sleep(0.1)
