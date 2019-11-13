#include <iostream>
#include <zconf.h>
#include "inaDevice.hpp"

int main()
{

	auto ina = inaDevice(0x40);
	std::cout << "Hello, World!" << std::endl;

	while (true) {
		std::cout << "---------------" << std::endl;
		std::cout << "current: " << ina.getShuntCurrent() << std::endl;
		std::cout << "voltage: " << ina.getBusVoltage() << std::endl;
		std::cout << "power: " << ina.getPower() << std::endl;
		sleep(1);
	}



	return 0;
}