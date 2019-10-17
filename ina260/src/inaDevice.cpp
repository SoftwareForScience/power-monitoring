#include "inaDevice.hpp"

ina_device::ina_device(unsigned devID)
{
	this->dev = ina_219_device_open(this->i2cpath, devID);

	if (!this->dev)
	{   throw std::invalid_argument("Invalid i2c device");  }

	badc = INA_219_DEVICE_BADC_12_BIT_128_AVERAGE;
	sadc = INA_219_DEVICE_SADC_12_BIT_128_AVERAGE;

	ina_219_device_config(this->dev, INA_219_DEVICE_BUS_VOLTAGE_RANGE_32 |
	                           INA_219_DEVICE_GAIN_8 |
	                           INA_219_DEVICE_MODE_SHUNT |
	                           INA_219_DEVICE_MODE_BUS |
	                           badc | sadc);

	ina_219_device_calibrate(this->dev, 0.1, 1.0);
}

ina_device::~ina_device()
{   ina_219_device_close(this->dev);    }

