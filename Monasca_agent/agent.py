from monasca_agent.forwarder.api import monasca_api
from ina219 import INA219, DeviceRangeError
import time
import psutil

SHUNT_OHMS = 0.1
MAX_EXPECTED_AMPS = 2.0
ina = INA219(SHUNT_OHMS, MAX_EXPECTED_AMPS)
ina.configure(ina.RANGE_16V)

REQUEST_TIME = Summary('request_processing_seconds',
'Time spent processing request')

PowerMeasurement = ina.power()
CurrentMeasurement = abs(ina.current()

if __name__ == '__main__':
	while True:
	post_metrics(self, PowerMeasurement)
	post_metrics(self, CurrentMeasurement)
