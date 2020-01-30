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
#include "server.hpp"
#include "../lib/pugixml/src/pugixml.hpp"
#include "../lib/date/include/date/date.h"

namespace fs = std::filesystem;

class logger
{
public:
	/*
	 * @brief Initializes output folder if it doesn't exist, checks and loads config file
	 * @param outputDir Path to output directory
	 * @param config Path to config file
	 * @port port for the client to contact servers on
	 */
	explicit logger(fs::path outputDir, const fs::path &config, int port);

	/* @brief starts reading from the INA's and writing output to output directory */
	void startMea();
	/* @brief ... the same as the other one but it now _stops_ it */
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
	Server server_ = Server();

	fs::path outDir, runDir;
	std::vector<piContainer> nodes;
};


#endif //INA260_LOGGER_HPP
