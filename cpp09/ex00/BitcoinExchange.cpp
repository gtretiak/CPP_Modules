#include "BitcoinExchange.hpp"
#include <map>
#include <string>

// Orthodox Canonical Form:
BitcoinExchange::BitcoinExchange () : DBPath_("./DataBase/data.csv") {
	this->data_ = loadDB(DBPath_);
} 
BitcoinExchange::BitcoinExchange(const std::string &DBPath) : DBPath_(DBPath) {
	this->data_ = loadDB(DBPath_);
}
BitcoinExchange::BitcoinExchange(const BitcoinExchange &An) : DBPath_(An.DBPath_), data_(An.data_) {}
BitcoinExchange	&BitcoinExchange::operator=(const BitcoinExchange &An) {
	if (this != &An)
	{
		this->DBPath_ = An.DBPath_;
		this->data_ = An.data_;
	}
	return *this;
}
BitcoinExchange::~BitcoinExchange() {}

// Public member function:
void	BitcoinExchange::processQuery(const std::string &filename) {
       	// std::getline, std::stringstream, atof, strtod
	std::ifstream	file(filename.c_str());
	if (!file.is_open())
		throw std::runtime_error("Error: could not open input file.");
	//throw allocation error ?
	std::string	line;
	while (std::getline(file, line))
	{
		std::stringstream	ss(line);
		std::string	date;
		std::string	valueStr;
		std::getline(ss, date, '|');
		std::getline(ss, valueStr);
		if (line is malformatted)
		{
			std::cerr << "Error: " << errorFormat << what << std::endl;
			continue ;
		}
		std::string	date;
		if (!isValidDate(date))
		{
			std::cerr << "Error: " << errorDate << std::endl;
			continue ;
		}
		char	*end;
		double	value = std::strtod(valueStr.c_str(), &end);
		if (*end != '\n' || *end != '\0')
		if (!isValidValue(value))
		{
			std::cerr << "Error: " << errorValue << std::endl;
			continue ;
		}

		double	res = getExchangeRate()// TODO
		compute() //TODO
		std::cout << line << std::endl; // printResult TODO
	}
	file.close();
}

// Internal Functions (helpers):
void	BitcoinExchange::loadDB(const std::string &filename) {
	std::ifstream	file(filename.c_str());
	if (!file.is_open())
		throw std::runtime_error("Error: could not open database.");
	std::string	line;
	while (std::getline(file, line))
	{
		std::string	date;
		double		price;
		//validate line
		//throw if database corrupted (invalid format)
		//assign pair: this->data_[date] = price;
	}
	file.close();
}
bool	BitcoinExchange::isValidDate(const std::string &date) const {
}
bool	BitcoinExchange::isValidValue(const double &value) const {
}
double	BitcoinExchange::getExchangeRate(std::map<std::string, double>::const_iterator it) {
	map.lower_bound() //TODO
}
