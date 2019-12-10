#include <iostream>
#include "logger.hpp"
#include "../lib/args/args.hxx"

int main(int argc, char **argv)
{
	std::cout << "Hello, World!" << std::endl;

	args::ArgumentParser parser("Logger options", "* required");
	args::HelpFlag help(parser, "help", "Display this help menu", {'h', "help"});
	args::Group arguments(parser, "arguments", args::Group::Validators::DontCare, args::Options::Global);
	args::ValueFlag<std::string> dir(arguments, "output directory", "(*) Path to output directory",
			{'d', "outputDirectory"});
	args::ValueFlag<std::string> cfg(arguments, "config file", "(*) Path to config xml file",
            {'c', "config"});
	args::ValueFlag<int> prt(arguments, "networking port", "Defaults to 20001",
            {'p', "port"});
	args::CompletionFlag completion(parser, {"complete"});

	try
	{   parser.ParseCLI(argc, argv);    }
	catch (args::Help)
	{
		std::cout << parser;
		return 1;
	}
	catch (args::Error& e)
	{
		std::cerr << e.what() << std::endl << parser;
		return 1;
	}

	if (!dir || !cfg)
	{
		std::cerr << "Not enough arguments given, run with -h option for more details" << std::endl;
		return 1;
	}

	auto logger_ = logger(args::get(dir), args::get(cfg), args::get(prt));

	logger_.startMea();

	getchar();

	logger_.stopMea();

	return 0;
}