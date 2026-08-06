#include "BitcoinExchange.hpp"
#include <map>
#include <string>
#include <iostream>

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
	std::ifstream	file(filename.c_str());
	if (!file.is_open())
		throw std::runtime_error("Error: could not open input file.");
	std::string	line;
	std::getline(file, line);
	verifyHeader(line, false);
	while (std::getline(file, line))
	{
		parseLine(line, false);
		if (this->resDate_ || this->resValue_)
		{
			printErrors(this->resDate_, this->resValue_);
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
	std::getline(file, line);
	verifyHeader(line, true);
	while (std::getline(file, line))
	{
		parseLine(line, true);
		double		price;
		//assign pair: this->data_[date] = price;
	}
	file.close();
}
void	BitcoinExchange::verifyHeader(std::string &header, bool isDB) {
	std::stringstream	ss(header);
	std::string	first, second;
	if (isDB)
		std::getline(ss, first, ',');
	else
		std::getline(ss, first, '|');
	std::getline(ss, second);
	if (isDB && (first != "date" || second != "exchange_rate"))
		throw std::runtime_error("Error: Data base malformatted.");
	if (!isDB && (first != "date" || second != "value"))
		throw std::runtime_error("Error: Input files malformatted.");
}
void	BitcoinExchange::parseLine(std::string	&line, bool isDB) {
	std::stringstream	ss(line);
	if (isDB)
		std::getline(ss, this->currentDate_, ',');
	else
		std::getline(ss, this->currentDate_, '|');
	std::getline(ss, this->currentValueStr_);
	//throw if database corrupted (invalid format)
	//validate line
	//format date
	//store value
	if (!isDB)
	{
		this->resDate_ = isValidDate(this->currentDate_);
		this->resValue_ = isValidValue(this->currentValue_);
	}
	//
	char	*end;
	double	value = std::strtod(valueStr.c_str(), &end);
	if (*end != '\n' || *end != '\0')
	if (!isValidValue(value))
	{
		std::cerr << "Error: " << errorValue << std::endl;
		continue ;
	}
}
void	BitcoinExchange::printErrors(ValidationResult date, ValidationResult value) const {
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
}
ValidationResult	BitcoinExchange::isValidDate(const std::string &date) const {
	if (wrong)
		return 1;
	return 0;
}
ValidationResult	BitcoinExchange::isValidValue(const double &value) const {
	if (wrong type)
		return 2;
	else if (value < 0)
		return 3;
	else if (value > 1000)
		return 4;
	return 0;
}
double	BitcoinExchange::getExchangeRate(const std::string &value) {
	map.lower_bound()
}
