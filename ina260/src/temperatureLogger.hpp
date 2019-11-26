//
// Created by Stefan Schokker on 2019-11-22.
//

#ifndef INA260_TEMPERATURELOGGER_HPP
#define INA260_TEMPERATURELOGGER_HPP

#include <filesystem>
#include <string>
#include <thread>
#include <fstream>
#include "client.hpp"
#include "../lib/date/include/date/date.h"

namespace fs = std::filesystem;

class temperatureLogger
{
public:
	temperatureLogger(fs::path outDir, std::vector<std::string> hostnames);

private:
	friend class logger;

	struct piTContainer {
		std::ofstream file;
		std::string name;
	};

	bool stop = false;
	void startLog();
	void stopLog();

	void run();
	std::thread* thread;

	Client client_ = Client(std::vector<std::string>());

	std::vector<piTContainer> nodes;
};


#endif //INA260_TEMPERATURELOGGER_HPP
