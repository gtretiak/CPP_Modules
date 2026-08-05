#ifndef BITCOINEXCHANGE_HPP
#define BITCOINEXCHANGE_HPP
#include <map>
#include <string>

class	BitcoinExchange {
	private:
		std::string	DBPath_;
		std::map<std::string, double>	data_;
		bool	isValidDate(const std::string &date) const;
		bool	isValidValue(const double &value) const;
		double	getExchangeRate(std::map<std::string, double>::const_iterator it);// TODO parametr
		void	loadDB(const std::string &filename);
	public:
		BitcoinExchange(); // "./DataBase/data.csv" by default
		BitcoinExchange(const std::string &DBPath);
		BitcoinExchange(const BitcoinExchange &An);
		BitcoinExchange	&operator=(const BitcoinExchange &An);
		~BitcoinExchange();
		void	processQuery(const std::string &filename);
};

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
