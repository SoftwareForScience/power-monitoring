#ifndef INA260_I2CDEVICE_HPP
#define INA260_I2CDEVICE_HPP

#include <cstddef>

// this is a helper class from another project,
// makes it easier to port to another library in the case that wiringPi gets deprecated

class I2CDevice {
public:
	I2CDevice(int id);

	virtual void init();
	int send(const void *data, size_t size);
	int writeReg8(int reg, int data);
	int writeReg16(int reg, int data);
	int readReg8(int reg);
	int readReg16(int reg);

private:
	int id;
protected:
	int handle;
};


#endif //INA260_I2CDEVICE_HPP
