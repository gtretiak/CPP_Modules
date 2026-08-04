#include "BitcoinExchange.hpp"
#include <map>
#include <string>

BitcoinExchange::BitcoinExchange () : DBPath_("./DataBase/data.csv") {
	this->data_ = loadDB(DBPath_);
} 
BitcoinExchange::BitcoinExchange(const std::string &DBPath) : DBPath_(DBPath) {}
BitcoinExchange(const BitcoinExchange &An) {}
BitcoinExchange	&operator=(const BitcoinExchange &An) {}
void	BitcoinExchange::loadDB(const std::string &filename) {
       	// std::ifstream, std::getline, std::stringstream, atof, strtod
}
int	BitcoinExchange::processQuery(const std::string &filename) {
	
	return 0;
}
bool	BitcoinExchange::isValidDate_(const std::string &date) const {}
bool	BitcoinExchange::isValidValue_(const double &value) const {}
double	BitcoinExchange::getExchangeRate_(iterator?) const {} //TODO
DataBaseException {}; // TODO?

/*
Summary Checklist:
Read data.csv, parse comma, store in map.
Read input.txt.
For each line:
Validate date format (check for YYYY-MM-DD).
Validate pipe |.
Validate value (0 to 1000).
Find rate in map. with map.lower_bound(date) finds the element that is >= date (if doesn't match previos one)
Multiply and print.*/

#endif
