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
#include <thread>
#include <utility>
#include <zconf.h>
#include <chrono>
#include "inaDevice.hpp"
#include "../lib/pugixml/src/pugixml.hpp"
#include "../lib/date/include/date/date.h"

namespace fs = std::filesystem;

class logger
{
public:
	explicit logger(std::filesystem::path outputDir);
	void loadFile(std::filesystem::path piXML);
	void startMea();
	void stopMea();
private:
	struct inaContainer
	{
		inaDevice *ina;
		std::ofstream file;
	};

	void run();

	bool stop = false;
	std::thread* thread;

	fs::path outDir, runDir;
	std::map<std::string, inaContainer> nodes;
};


#endif //INA260_LOGGER_HPP
