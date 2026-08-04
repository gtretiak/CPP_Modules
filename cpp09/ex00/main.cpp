#include "BitcoinExchange.hpp"
#include <string>

int	main(int argc, char **argv) {
	if (argc == 2)
	{
		const std::string	DBPath = "./DataBase/data.csv";
		BitcoinExchange	btc(&DBPath);
		return (BitcoinExchange.processQuery(argv[1]));
	}
	std::cerr << "Invalid number of arguments. Query in format \"date | value\" expected" << std::endl;
	return 1;
}
