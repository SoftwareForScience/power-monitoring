import time
import board
import busio
import adafruit_ina260
from adafruit_bus_device.i2c_device import I2CDevice     
#i2c = busio.I2C(board.SCL, board.SDA)
i2c = board.I2C();


#while not i2c.try_lock():
#	pass

#device = I2CDevice(i2c, 0x40)
ina260 = adafruit_ina260.INA260(i2c)

#i22c = board.I2C()
#ina261 = adafruit_ina260.INA260(i22c)

while True:
	print("Current: %.2f mA Voltage: %.2f V Power:%.2f mW"
		%(ina260.current, ina260.voltage, ina260.power))
#	print("Current1: %.2f mA Voltage: %.2f v Power:%.2f mW" 
#		%(ina261.current, ina261.voltage, ina261.power))
	time.sleep(1)

i2c.unlock()
