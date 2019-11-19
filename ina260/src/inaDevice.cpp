#include <iostream>
#include "inaDevice.hpp"

inaDevice::inaDevice(int id) : I2CDevice(id)
{
	I2CDevice::init();

	// Defines from INASettings.hpp
	uint16_t config = INA260_CONFIG_AVGRANGE_128 |
	                  INA260_CONFIG_BVOLTAGETIME_140US |
	                  INA260_CONFIG_SCURRENTTIME_140US |
	                  INA260_CONFIG_MODE_SANDBVOLT_CONTINUOUS;

	config = (config << 8 | config >> 8) & 0xFFFF;

	this->writeReg16(INA260_REG_CONFIG, config);
}

double inaDevice::getShuntCurrent()
{
	uint16_t res = inaDevice::invert(this->readReg16(INA260_REG_SHUNTCURRENT));
	return (double)res * 0.00125;   // INA has 1.25 mV steps
}

double inaDevice::getBusVoltage()
{
	uint16_t res = inaDevice::invert(this->readReg16(INA260_REG_BUSVOLTAGE));
	return (double)res * 0.00125;   // INA has 1.25 mV steps
}

double inaDevice::getPower()
{
	uint16_t res = inaDevice::invert(this->readReg16(INA260_REG_POWER));
	return (double)res / 100;  // Convert to Watts
}

uint16_t inaDevice::invert(uint16_t a)
{   return (a << 8 | a >> 8) & 0xFFFF;  }