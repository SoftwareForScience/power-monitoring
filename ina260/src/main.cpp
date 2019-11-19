#include <iostream>
#include <zconf.h>
#include "inaDevice.hpp"
#include "logger.hpp"

int main()
{

	std::cout << "Hello, World!" << std::endl;

	auto logger_ = logger("/home/pi/somedumbpath");
	logger_.loadFile("/tmp/tmp.zSq6XiHiX7/pis.xml");

	logger_.startMea();

	sleep(20);

	logger_.stopMea();


	return 0;
}