#include <iostream>
#include <zconf.h>
#include "logger.hpp"

int main()
{

	std::cout << "Hello, World!" << std::endl;

	auto logger_ = logger("/home/pi/somedumbpath", "/tmp/tmp.zSq6XiHiX7/pis.xml");

	logger_.startMea();

	getchar();

	logger_.stopMea();

	return 0;
}