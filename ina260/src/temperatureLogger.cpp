//
// Created by Stefan Schokker on 2019-11-22.
//

#include "temperatureLogger.hpp"

namespace ch = std::chrono;

temperatureLogger::temperatureLogger(fs::path outDir, std::vector<std::string> hostnames)
{
	for (auto &a : hostnames)
	{
		fs::path outFile = outDir.string() + a + "-temp.csv";
		this->nodes.emplace_back(piTContainer{
				.file = std::ofstream(outFile), .name = a
		});

		std::cout << "outfile :" << outFile.string() << "\n";

		this->nodes.back().file << "date, time, name, dcelcius\n";
		this->nodes.back().file.flush();
	}

	this->client_ = Client(hostnames);
}

void temperatureLogger::startLog()
{
	this->stop = false;
	this->thread = new std::thread(&temperatureLogger::run, this);
	this->thread->detach();
}

void temperatureLogger::stopLog()
{
	this->stop = true;
	if (this->thread->joinable())
	{   this->thread->join();   }

	for (auto &node : this->nodes)
	{
		if (node.file.is_open())
		{   node.file.close();   }
	}
}

void temperatureLogger::run()
{
	while (!stop)
	{
		auto now = ch::high_resolution_clock::now();
		std::string ftime = date::format("%F, %T", date::floor<ch::milliseconds>(ch::system_clock::now()));
		std::map<std::string, std::string> temps = this->client_.Call();

		for (auto &a : this->nodes)
		{
			std::cout << a.name << std::endl;
			std::string entry = ftime +                         //  Date
			                    ", " + a.name +                 //  Name
			                    ", " + temps[a.name] + "\n";    //  Temperature
			a.file << entry;
			a.file.flush();
		}
		usleep(100000);
	}
}