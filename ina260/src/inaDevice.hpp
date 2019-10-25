#ifndef INA260_INADEVICE_HPP
#define INA260_INADEVICE_HPP

#include <stdexcept>

#include "../lib/ina219-linux-lib/ina219.h"

class ina_device
{
public:
	explicit ina_device(unsigned devID);
	~ina_device();

private:
	std::string i2cpath = "/dev/i2c-1";
	ina_219_device *dev;
};


#endif //INA260_INADEVICE_HPP
