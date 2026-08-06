#ifndef BITCOINEXCHANGE_HPP
#define BITCOINEXCHANGE_HPP
#include <map>
#include <string>

class	BitcoinExchange {
	private:
		std::string	DBPath_;
		std::map<std::string, double>	data_;
		std::string	currDate_;
		std::string	currValueStr_;
		double		currValue_;
		ValidationResult	resDate_;
		ValidationResult	resValue_;

		void	loadDB(const std::string &filename);
		void	verifyHeader(std::string &header, bool isDB);
		void	parseLine(std::string &line, bool isDB);
		void	printErrors(ValidationResult Date, ValidationResult value) const;
		ValidationResult	isValidDate(const std::string &date) const;
		ValidationResult	isValidValue(const double &value) const;
		double	getExchangeRate(const std::string &value);
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
	BAD_TYPE,
	NEGATIVE,
	TOO_LARGE
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
