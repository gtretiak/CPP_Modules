#include "BitcoinExchange.hpp"
#include <map>
#include <string>
#include <sstream>
#include <iostream>

// Orthodox Canonical Form:
BitcoinExchange::BitcoinExchange () : DBPath_("./DataBase/data.csv") {
	this->data_ = loadDB(DBPath_);
} 
BitcoinExchange::BitcoinExchange(const std::string &DBPath) : DBPath_(DBPath) {
	loadDB();
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
	std::getline(file, line); // to discard the first line
	while (std::getline(file, line))
	{
		parseLine(line, false);
		if (this->resDate_ || this->resValue_)
		{
			printErrors();
			continue ;
		}
		double	res = Exchange();
		std::cout << this->currentDate_ << " => " << this->currentValue_ << " = " << res << std::endl;
	}
	file.close();
}

// Internal Functions (helpers):
void	BitcoinExchange::loadDB() {
	std::ifstream	file(this->DBPath_.c_str());
	if (!file.is_open())
		throw std::runtime_error("Error: could not open database.");
	std::string	line;
	std::getline(file, line); // to discard the first line
	while (std::getline(file, line))
	{
		parseLine(line, true);
		//verify each line to avoid later comparison with garbage
		convertDate();
		this->data_[this->currentDate_] = this->currentValue_;
	}
	file.close();
}
void	BitcoinExchange::parseLine(std::string	&line, bool isDB) {
	std::stringstream	ss(line);
	//verify each line of DB to avoid comparison with garbage; throw
	//verify each line of FILE; print errors and continue
	if (isDB)
	{
		std::getline(ss, this->currentDate_, ',');
		if (this->currentDate_.empty())
			throw std::runtime_error("Error: bad input => " + this->currentDate_);
	}
	else
		std::getline(ss, this->currentDate_, '|');
	std::getline(ss, this->currentValueStr_);
	if (!isDB)
	{
		this->resDate_ = isValidDate(this->currentDate_);
		this->resValue_ = isValidValue(this->currentValue_);
	}
	//
	char	*end;
	this->currentValue_ = std::strtod(this->currentValueStr_.c_str(), &end);
	if (*end != '\n' || *end != '\0')
		std::cerr << "Error: bad input => " << this->currentValueStr_ << std::endl;
	if (!isValidValue(value))
	{
		std::cerr << "Error: " << e`rrorValue << std::endl;
		continue ;
	}
}
void	BitcoinExchange::convertDate() {
	std::string	month, day, year;
	std::stringstream	ss(this->currentDate_);
	std::getline(ss, month, '/');
	std::getline(ss, day, '/');
	std::getline(ss, year);
	std::ostringstream	out;
	out << year << '-' << std::setw(2) << std::setfill('0') << month << '-' << std::setw(2) << std::setfill('0') << day;
	this->currentDate_ = out.c_str();
}
void	BitcoinExchange::printErrors() const {
	if (this->resDate_)
		std::cerr << "Error: bad input => " << this->resDate_ << std::endl;
	switch (this->resValue_)
	{
		case (0):
			return ;
		case (2):
			std::cerr << "Error: not positive number." << std::endl;
			break ;
		case (3):
			std::cerr << "Error: too large number." << std::endl;
			break ;

	}
}
ValidationResult	BitcoinExchange::isValidDate() {
	if (wrong)
	// length = 10
	// index 4 and 7 should be '-'
	// rest are digits
	// extracting to year, month, day
	// range 1-12 for month, 1-31 for day (but not always), leap years
		return 1;
	return 0;
}
ValidationResult	BitcoinExchange::isValidValue(const double &value) const {
	if (value < 0)
		return 2;
	else if (value > 1000)
		return 3;
	return 0;
}
double	BitcoinExchange::Exchange(const std::string &value) {
	map.lower_bound()
}
