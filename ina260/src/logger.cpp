//
// Created by Stefan Schokker on 2019-11-14.
//

#include "logger.hpp"

logger::logger(std::filesystem::path outputDir)
{

}

void logger::loadFile(std::filesystem::path piXML)
{
	if (!std::filesystem::exists(piXML))
	{   throw std::runtime_error("File [" + piXML.string() + "] does not exist");   }

	pugi::xml_document doc;
	doc.load_file(piXML.c_str());

	pugi::xpath_query pi_query("/list/pi");
	pugi::xpath_query name_query("hostname/text()");
	pugi::xpath_query i2c_query("i2c/text()");

	pugi::xpath_node_set piList = doc.select_nodes(pi_query);

	for (pugi::xpath_node xpath_pi : piList)
	{
		pugi::xml_node pi = xpath_pi.node();
		pugi::xml_node name = pi.select_node(name_query).node();
		pugi::xml_node i2c = pi.select_node(i2c_query).node();

		std::cout << "hostname: " << name.value();
		std::cout << " - i2c address: " << i2c.value() << std::endl;
	}

}