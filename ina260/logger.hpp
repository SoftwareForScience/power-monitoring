//
// Created by Stefan Schokker on 2019-11-14.
//

#ifndef INA260_LOGGER_HPP
#define INA260_LOGGER_HPP

#include <map>
#include <string>
#include <fstream>
#include <filesystem>
#include <iostream>
#include <thread>
#include <utility>
#include <zconf.h>
#include <chrono>
#include "inaDevice.hpp"
#include "temperatureLogger.hpp"
#include "../lib/pugixml/src/pugixml.hpp"
#include "../lib/date/include/date/date.h"

namespace fs = std::filesystem;

class logger
{
public:
	explicit logger(fs::path outputDir, const fs::path& config);

	void startMea();
	void stopMea();
private:
	struct piContainer
	{
		std::string name;
		inaDevice *ina;
		std::ofstream file;
	};

	void run();
	void loadConfig(fs::path piXML);

	bool stop = false;
	std::thread* thread;
	temperatureLogger tlog = temperatureLogger("", std::vector<std::string>());

	fs::path outDir, runDir;
	std::vector<piContainer> nodes;
};


#endif //INA260_LOGGER_HPP
