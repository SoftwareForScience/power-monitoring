//
// Created by Stefan Schokker on 2019-11-14.
//

#include "logger.hpp"

namespace fs = std::filesystem;
namespace ch = std::chrono;

logger::logger(fs::path outputDir, const fs::path &config, int port)
{
	if (!fs::exists(outputDir))
	{
		std::cout << "[INFO] Given output directory does not exist, I'm creating it for you.\n";
		fs::create_directory(outputDir);
	}

	this->loadConfig(config);

	this->outDir = std::move(outputDir);
}

void logger::startMea()
{
	this->runDir = this->outDir.string() + "/" +
			date::format("%F %T", date::floor<ch::milliseconds>(ch::system_clock::now())) + "/";

	if (!fs::exists(this->runDir))
	{   fs::create_directory(this->runDir);   }

	// Get hostnames and start temperature client
	std::vector<std::string> hostnames;
	for (auto &node : this->nodes)
	{   hostnames.emplace_back(node.name);    }

	this->tlog = temperatureLogger(this->runDir, hostnames);

	// Initialise CSV files for all pi's
	for (auto &node : this->nodes)
	{
		fs::path outFile = this->runDir.string() + node.name + ".csv";
		std::cout << "outfile: " << outFile.string() << std::endl;
		node.file = std::ofstream(outFile);
		node.file << "date, time, name, amps, volts, watts\n";
		node.file.flush();
	}

	this->tlog.startLog();

	// Start thread and return to main thread
	this->thread = new std::thread(&logger::run, this);
	this->thread->detach();
}

void logger::stopMea()
{
	// Wait for thread to exit
	this->stop = true;
	if (this->thread->joinable())
	{   this->thread->join();   }

	this->tlog.stopLog();

	for (auto &node : this->nodes)
	{
		if (node.file.is_open())
		{   node.file.close();   }
	}
}

void logger::run()
{
	while (!this->stop)
	{
		auto now = ch::high_resolution_clock::now();
		std::string ftime = date::format("%F, %T", date::floor<ch::milliseconds>(ch::system_clock::now()));

		// Get and write measurements to file
		for (auto& node : this->nodes)
		{
			// CSV string formatting
			std::string entry = ftime +                                         //  Date
					", " + node.name +                                          //  name
					", " + std::to_string(node.ina->getShuntCurrent()) +        //  amps
					", " + std::to_string(node.ina->getBusVoltage()) +          //  volts
					", " + std::to_string(node.ina->getPower()) + "\n";         //  power
			node.file << entry;
		}

		// Make this into a more or less periodical task
		auto later = ch::high_resolution_clock::now();
		ch::duration<double> time_span = ch::duration_cast<ch::microseconds>(later - now);

		usleep(500000/* - time_span.count()*/);
	}
}

void logger::loadConfig(fs::path piXML)
{
	if (!fs::exists(piXML))
	{   throw std::runtime_error("File [" + piXML.string() + "] does not exist");   }

	pugi::xml_document doc;
	doc.load_file(piXML.c_str());

	// Prepare xpath queries for hostname and i2c address
	pugi::xpath_query pi_query("/list/pi");
	pugi::xpath_query name_query("hostname/text()");
	pugi::xpath_query i2c_query("i2c/text()");

	// Get all pi elements from XML file
	pugi::xpath_node_set piList = doc.select_nodes(pi_query);

	for (pugi::xpath_node xpath_pi : piList)
	{
		// Get hostname and i2c address from pi node
		pugi::xml_node pi = xpath_pi.node();
		pugi::xml_node name = pi.select_node(name_query).node();
		pugi::xml_node i2c = pi.select_node(i2c_query).node();

		// Prepare and insert new pi + ina combination into map for later use
		this->nodes.emplace_back(piContainer
		{
			.name = name.value(),
			.ina = new inaDevice(std::stoi(i2c.value(), nullptr, 16))
		});
	}
}