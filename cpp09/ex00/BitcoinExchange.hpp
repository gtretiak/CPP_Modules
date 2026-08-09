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
		double		currentValueD_;

		void	loadDB();
		int	parseLine(std::string &line, bool isDB);
	//	void	convertDate();
		std::string	trimSpaces(const std::string &str) const;
		bool	isValidDate() const;
		bool	isValidValue();
		double	getExchangeRate() const;
	public:
		BitcoinExchange(); // "./DataBase/data.csv" by default
		BitcoinExchange(const std::string &DBPath);
		BitcoinExchange(const BitcoinExchange &An);
		BitcoinExchange	&operator=(const BitcoinExchange &An);
		~BitcoinExchange();

		void	processQuery(const std::string &inputFilename); 
};

#endif
