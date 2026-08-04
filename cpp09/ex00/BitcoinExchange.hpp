#ifndef BITCOINEXCHANGE_HPP
#define BITCOINEXCHANGE_HPP
#include <map>

class	BitcoinExchange {
	private:
		std::map<std::string, double>	data_;
		bool	isValidDate(const std::string &date) const;
		bool	isValidValue(const double &value) const;
		double	getExchangeRate(const std::string &date) const;
		DataBaseException {}; // TODO
	public:
		void	loadDB(std::string filename); // std::ifstream, std::getline, std::stringstream, atof, strtod
		void	processQuery(std::string filename);
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
