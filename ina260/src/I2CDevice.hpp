//
// Created by Stefan Schokker on 2019-11-13.
//

#ifndef INA260_I2CDEVICE_HPP
#define INA260_I2CDEVICE_HPP


#include <cstddef>

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
