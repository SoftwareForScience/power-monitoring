#include <iostream>
#include <zconf.h>
#include "inaDevice.hpp"
#include "logger.hpp"

int main()
{

	std::cout << "Hello, World!" << std::endl;

	auto logger_ = logger("/home/pi/somedumbpath");
	logger_.loadFile("/tmp/tmp.zSq6XiHiX7/pis.xml");

//	while (true) {
//		std::cout << "---------------" << std::endl;
//		std::cout << "current: " << ina.getShuntCurrent() << std::endl;
//		std::cout << "voltage: " << ina.getBusVoltage() << std::endl;
//		std::cout << "power: " << ina.getPower() << std::endl;
//		sleep(1);
//	}



	return 0;
}