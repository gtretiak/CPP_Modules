#ifndef BITCOINEXCHANGE_HPP
#define BITCOINEXCHANGE_HPP
#include <map>

class	BitcoinExchange {
	private:
		std::map<std::string, float>	data_;
		bool	isValidDate(std::string date) const;
		bool	isValidValue(double value) const;
		float	getExchangeRate(std::string date) const;
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
Find rate in map.
Multiply and print.*/

#endif
