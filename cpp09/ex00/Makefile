NAME = btc 
FLAGS = -Wall -Wextra -Werror -std=c++98 -g
SRC = main.cpp BitcoinExchange.cpp
OBJ = $(addprefix ./, $(SRC:%.cpp=%.o))

all: $(NAME)

$(NAME): $(OBJ)
	@c++ $(OBJ) -o $(NAME)

%.o:%.cpp
	@c++ $(FLAGS) -c $< -o $@

.PHONY: clean fclean re

clean:
	@rm -rf $(OBJ)
	@echo "Objects removed"

fclean: clean
	@rm -rf $(NAME)
	@echo "Program removed"

re: fclean all
