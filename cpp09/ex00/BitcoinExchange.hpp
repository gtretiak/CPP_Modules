#ifndef BITCOINEXCHANGE_HPP
#define BITCOINEXCHANGE_HPP
#include <map>
#include <string>

class	BitcoinExchange {
	private:
		std::string	DBPath_;
		std::map<std::string, double>	data_;
		std::string	currentDate_;
		std::string	currentValueStr_;
		double		currentValue_;
		ValidationResult	resDate_;
		ValidationResult	resValue_;

		void	loadDB();
		void	parseLine(std::string &line, bool isDB);
		void	convertDate();
		void	printErrors() const;
		ValidationResult	isValidDate(const std::string &date) const;
		ValidationResult	isValidValue(const double &value) const;
		double	Exchange();
	public:
		BitcoinExchange(); // "./DataBase/data.csv" by default
		BitcoinExchange(const std::string &DBPath);
		BitcoinExchange(const BitcoinExchange &An);
		BitcoinExchange	&operator=(const BitcoinExchange &An);
		~BitcoinExchange();

		void	processQuery(const std::string &filename);
};

enum	ValidationResult {
	VALID,
	BAD_DATE,
	NEGATIVE,
	TOO_LARGE
};

/*
For each line:
Validate date format (check for YYYY-MM-DD).
Validate pipe |.
Find rate in map. with map.lower_bound(date) finds the element that is >= date (if doesn't match previos one)
Multiply and print.*/

#endif
