#ifndef SCALARCONVERTER_HPP
#define SCALARCONVERTER_HPP
#include <string>

class	ScalarConverter {
	private:
		ScalarConverter();
		ScalarConverter(const ScalarConverter &An);
		ScalarConverter	&operator=(const ScalarConverter &An);
		~ScalarConverter();
		enum	Type_ {
			CHAR,
			INT,
			FLOAT,
			DOUBLE,
			PSEUDO_F,
			PSEUDO_D,
			INVALID
		};
		static ScalarConverter::Type_	detectType(const std::string &var);
		static double	parse(ScalarConverter::Type_ type, const std::string &var);
		static void	printChar(double num);
		static void	printInt(double num);
		static void	printFloat(double num);
		static void	printDouble(double num);
	public:
		static void	convert(const std::string &var);
};

#endif
