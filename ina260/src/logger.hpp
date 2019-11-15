//
// Created by Stefan Schokker on 2019-11-14.
//

#ifndef INA260_LOGGER_HPP
#define INA260_LOGGER_HPP

#include <map>
#include <string>
#include <filesystem>
#include <fstream>
#include <iostream>
#include "inaDevice.hpp"
#include "../lib/pugixml/src/pugixml.hpp"

class logger
{
public:
	explicit logger(std::filesystem::path outputDir);
	void loadFile(std::filesystem::path piXML);
private:
	class inaContainer
	{
	public:
		inaDevice *ina;
		std::string name;
		std::ofstream file;
	};

	std::map<std::string, inaContainer> inas;
};


#endif //INA260_LOGGER_HPP
