#include "BitcoinExchange.hpp"
#include <string>
#include <iostream>

int	main(int argc, char **argv) {
	if (argc == 2)
	{
		try
		{
			std::string	DBPath = "./db.csv";
			BitcoinExchange	btc(DBPath);
			btc.processQuery(argv[1]);
		}
		catch(const std::exception& e)
		{
			std::cerr << e.what() << std::endl;
			return 1;
		}
		return 0;
	}
	std::cerr << "Invalid number of arguments. Input file with queries in format \"date | value\" expected" << std::endl;
	return 1;
}
