#include <iostream>
#include "inaDevice.hpp"

int main()
{
	std::cout << "Hello, World!" << std::endl;
	ina = ina_device(0x40);

	return 0;
}