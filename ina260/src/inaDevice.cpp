#include <iostream>
#include "inaDevice.hpp"

inaDevice::inaDevice(int id) : I2CDevice(id)
{
	I2CDevice::init();
	uint16_t config = INA260_CONFIG_AVGRANGE_128 |
	                  INA260_CONFIG_BVOLTAGETIME_140US |
	                  INA260_CONFIG_SCURRENTTIME_140US |
	                  INA260_CONFIG_MODE_SANDBVOLT_CONTINUOUS;

	config = ((config << 8) | config >> 8);

	this->writeReg16(INA260_REG_CONFIG, config);
}

float inaDevice::getShuntCurrent()
{
	uint16_t res = this->readReg16(INA260_REG_SHUNTCURRENT);
	res = (res << 8 | res >> 8) & 0xffff;
	return (float) res * 0.00125;
}

float inaDevice::getBusVoltage()
{
	uint16_t res = this->readReg16(INA260_REG_BUSVOLTAGE);
	res = (res << 8 | res >> 8) & 0xffff;
	return (float) res * 0.00125;
}

float inaDevice::getPower()
{
	uint16_t res = this->readReg16(INA260_REG_POWER);
	res = (res << 8 | res >> 8) & 0xffff;
	return (float) res / 1000;
}