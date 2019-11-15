#ifndef INA260_INADEVICE_HPP
#define INA260_INADEVICE_HPP

#include "I2CDevice.hpp"
#include "INASettings.hpp"
#include <cstdint>

class inaDevice : I2CDevice
{
public:
	explicit inaDevice(int id);

	double getShuntCurrent();
	double getBusVoltage();
	double getPower();

private:
	static uint16_t invert(uint16_t a);
};


#endif //INA260_INADEVICE_HPP
