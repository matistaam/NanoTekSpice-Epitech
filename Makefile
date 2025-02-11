##
## EPITECH PROJECT, 2025
## B-OOP-400-LYN-4-1-tekspice-matis.taam
## File description:
## Makefile
##

CXX				=	g++

CXXFLAGS		=	-std=c++20 -Wall -Wextra -Werror -g3

CPPFLAGS		=	-I./include

SRC_FILES		=	$(wildcard src/*.cpp) \
					$(wildcard src/*/*.cpp)

OBJ_FILES		=	$(SRC_FILES:.cpp=.o)

NAME			=	nanotekspice

RM				=	rm -f

all: $(NAME)

$(NAME): $(OBJ_FILES)
	$(CXX) $(CXXFLAGS) $(OBJ_FILES) -o $(NAME)

%.o: %.cpp
	$(CXX) $(CXXFLAGS) $(CPPFLAGS) -c $< -o $@

clean:
	$(RM) $(OBJ_FILES)

fclean: clean
	$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re
