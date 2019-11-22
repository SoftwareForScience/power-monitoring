//
// Created by Stefan Schokker on 2019-11-14.
//

#include "logger.hpp"

namespace fs = std::filesystem;
namespace ch = std::chrono;

logger::logger(fs::path outputDir)
{
	if (!fs::exists(outputDir))
	{
		std::cout << "[INFO] Given output directory does not exist, I'm creating it for you.\n";
		fs::create_directory(outputDir);
	}

	this->outDir = std::move(outputDir);
}

void logger::startMea()
{
	this->runDir = this->outDir.string() + "/" +
			date::format("%F %T", date::floor<ch::milliseconds>(ch::system_clock::now())) +
			"/";

	if (!fs::exists(this->runDir))
	{   fs::create_directory(this->runDir);   }

	for (auto &node : this->nodes)
	{
		fs::path outFile = this->runDir.string() + node.first + ".csv";
		std::cout << "outfile: " << outFile.string() << std::endl;
		node.second.file = std::ofstream(outFile);
		node.second.file << "date, name, amps, volts, watts, dcelcius\n";
	}

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

	for (auto &node : this->nodes)
	{
		if (node.second.file.is_open())
		{   node.second.file.close();   }
	}
}

void logger::run()
{
	while (!this->stop)
	{
		auto now = ch::high_resolution_clock::now();
		std::string ftime = date::format("%F %T", date::floor<ch::milliseconds>(ch::system_clock::now()));

		// Get and write measurements to file
		for (auto& node : this->nodes)
		{
			// CSV string formatting
			std::string entry = ftime +                                         //  Date
					", " + node.first +                                         //  name
					", " + std::to_string(node.second.ina->getShuntCurrent()) + //  amps
					", " + std::to_string(node.second.ina->getBusVoltage()) +   //  volts
					", " + std::to_string(node.second.ina->getPower()) +        //  power
					", Temperature not available\n";                            //  dcelcius
			node.second.file << entry;
		}

		// Make this into a more or less periodical task
		auto later = ch::high_resolution_clock::now();
		ch::duration<double> time_span = ch::duration_cast<ch::microseconds>(later - now);

		usleep(50000 - time_span.count());
	}
}

void logger::loadFile(fs::path piXML)
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
		this->nodes[name.value()] = inaContainer
		{   .ina = new inaDevice(std::stoi(i2c.value(), nullptr, 16))  };
	}
}