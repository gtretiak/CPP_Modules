NAME = abc
FLAGS = -Wall -Werror -Wextra -std=c++98 -g
SRC = main.cpp Functions.cpp Base.cpp A.cpp B.cpp C.cpp
OBJ = $(addprefix ./, $(SRC:%.cpp=%.o))

all: $(NAME)

$(NAME): $(OBJ)
	@c++ $(OBJ) -o $(NAME)
	@echo "Compiled!"

%.o: %.cpp
	@c++ $(FLAGS) -c $< -o $@

.PHONY: clean fclean re

clean:
	@rm -rf $(OBJ)
	@echo "Objects removed"

fclean: clean
	@rm -rf $(NAME)
	@echo "Program removed"

re: fclean all
