#include "BitcoinExchange.hpp"
#include <map>
#include <string>
#include <sstream> //stringstream, ostringstream
#include <iostream>
#include <fstream> // ifstream
#include <iomanip> //setw, setfill
#include <cstdlib> // strtod

// Orthodox Canonical Form:
BitcoinExchange::BitcoinExchange () : DBPath_("./DataBase/data.csv") {
	loadDB();
	if (this->data_.empty())
		throw std::runtime_error("Error: database contains no valid data.");
} 
BitcoinExchange::BitcoinExchange(const std::string &DBPath) : DBPath_(DBPath) {
	loadDB();
	if (this->data_.empty())
		throw std::runtime_error("Error: database contains no valid data.");
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
void	BitcoinExchange::processQuery(const std::string &inputFilename) {
	std::ifstream	file(inputFilename.c_str());
	if (!file.is_open())
		throw std::runtime_error("Error: could not open input file.");
	std::string	line;
	std::getline(file, line); // to discard the first line
	while (std::getline(file, line))
	{
		if (parseLine(line, false))
			continue ;
		double	rate = getExchangeRate();
		if (rate < 0)
			continue ;
		std::cout << this->currentDate_ << " => " << this->currentValueD_;
		std::cout << " = " << rate * this->currentValueD_ << std::endl;
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
		if (parseLine(line, true))
		{
			std::cerr << "Error: invalid database line: " << line << std::endl;
			continue ;
		}
		this->data_[this->currentDate_] = this->currentValueD_;
	}
	file.close();
}
int	BitcoinExchange::parseLine(std::string	&line, bool isDB) {
	line = trimSpaces(line);
	if (line.empty())
		return 1;
	std::stringstream	ss(line);
	if (isDB)
	{
		size_t pos = line.find(',');
		if (pos == std::string::npos
			|| line.find(',', pos + 1) != std::string::npos)
			throw std::runtime_error("Error: database malformatted");
		std::getline(ss, this->currentDate_, ',');
		std::getline(ss, this->currentValueStr_);
		if (this->currentDate_.empty()
			|| this->currentValueStr_.empty())
			return 1;
		//convertDate();
	}
	else
	{
		if (line[0] == '#')
			return 1;
		size_t pos = line.find('|');
		if (pos == std::string::npos
			|| line.find('|', pos + 1) != std::string::npos)
		{
			std::cerr << "Error: bad input => " << line << std::endl;
			return 1;
		}
		std::getline(ss, this->currentDate_, '|');
		std::getline(ss, this->currentValueStr_);
		if (this->currentDate_.empty()
			|| this->currentValueStr_.empty())
		{
			std::cerr << "Error: bad input => " << line << std::endl;
			return 1;
		}
	}
	this->currentDate_ = trimSpaces(this->currentDate_);
	this->currentValueStr_ = trimSpaces(this->currentValueStr_);
	if (!isValidDate())
	{
		if (isDB)
			return 1;
		std::cerr << "Error: wrong data format: " << this->currentDate_ << std::endl;
		return 1;
	}
	if (!isValidValue())
		return 1;
	return 0;
}
/*void	BitcoinExchange::convertDate() {
	std::string	month, day, year;
	std::stringstream	ss(this->currentDate_);
	std::getline(ss, month, '/');
	std::getline(ss, day, '/');
	std::getline(ss, year);
	std::ostringstream	out;
	out << year << '-' << std::setw(2) << std::setfill('0') << month << '-' << std::setw(2) << std::setfill('0') << day;
	this->currentDate_ = out.c_str();
}*/
std::string	BitcoinExchange::trimSpaces(const std::string &str) const {
	size_t	beginning = str.find_first_not_of(" \t");
	size_t	ending = str.find_last_not_of(" \t");
/*	size_t	space = str.find(beginning, ' ');
	if (space != std::string::npos)
		beginning = space;
	space = str.find(beginning, ' ');
	if (space != std::string::npos)
		ending = space - 1;*/
	return str.substr(beginning, ending - beginning + 1);
}
bool	BitcoinExchange::isValidDate() const {
	if (this->currentDate_.length() != 10)
		return false;
	if (this->currentDate_[4] != '-'
		|| this->currentDate_[7] != '-')
		return false;
	for (size_t i = 0; i < 10; i++)
	{
		if (!std::isdigit(static_cast<unsigned char>(this->currentDate_[i])) && i != 4 && i != 7)
			return false;
	}
	std::string	yearStr, monthStr, dayStr;
	std::stringstream	ss(this->currentDate_);
	std::getline(ss, yearStr, '-');
	std::getline(ss, monthStr, '-');
	std::getline(ss, dayStr);
	long	yD = std::strtol(yearStr.c_str(), NULL, 10);
	long	mD = std::strtol(monthStr.c_str(), NULL, 10);
	long	dD = std::strtol(dayStr.c_str(), NULL, 10);
	if (mD == 4 || mD == 6 || mD == 9 || mD == 11)
	{
		if (dD < 1 || dD > 30)
			return false;
	}
	else if (mD == 2)
	{
		if (yD % 400 == 0 || (yD % 4 == 0 && yD % 100 != 0)) // leap year
		{
			if (dD < 1 || dD > 29)
				return false;
		}
		else
		{
			if (dD < 1 || dD > 28)
				return false;
		}
	}
	else if (mD == 1 || mD == 3 || mD == 5 || mD == 7 || mD == 8 || mD == 10 || mD == 12)
	{
		if (dD < 1 || dD > 31)
			return false;
	}
	else
		return false;
	return true;
}
bool	BitcoinExchange::isValidValue() {
	char	*end;
	this->currentValueD_ = std::strtod(this->currentValueStr_.c_str(), &end);
	if (*end != '\0')
	{
		std::cerr << "Error: bad value: " << this->currentValueStr_ << std::endl;
		return false;
	}
	if (this->currentValueD_ < 0)
	{
		std::cerr << "Error: not positive number: " << this->currentValueD_ << std::endl;
		return false;
	}
	else if (this->currentValueD_ > 1000)
	{
		std::cerr << "Error: too big number: " << this->currentValueD_ << std::endl;
		return false;
	}
	return true;
}
double	BitcoinExchange::getExchangeRate() const {
	std::map<std::string, double>::const_iterator	it;
	it = this->data_.lower_bound(this->currentDate_);
	if (it == this->data_.end())
	{
		--it;
		return it->second;
	}
	else if (it->first == this->currentDate_)
		return it->second;
	else if (it == this->data_.begin())
	{
		std::cerr << "Date not found" << std::endl;
		return -1;
	}
	--it;
	return it->second;
}
