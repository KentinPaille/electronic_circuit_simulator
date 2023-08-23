##
## EPITECH PROJECT, 2023
## amogus
## File description:
## Makefile
##

NAME	=	nanotekspice

SRC		=	main.cpp \
			src/Elementaries/AndComponent.cpp \
			src/Elementaries/NotComponent.cpp \
			src/Elementaries/XorComponent.cpp \
			src/Elementaries/OrComponent.cpp \
			src/Specials/InputComponent.cpp \
			src/Specials/OutputComponent.cpp \
			src/Specials/Pin.cpp \
			src/Specials/TrueComponent.cpp \
			src/Specials/FalseComponent.cpp \
			src/Specials/ClockComponent.cpp \
			src/Shell.cpp \
			src/Parser.cpp \
			src/tools.cpp \
			src/Gates/Gate4081.cpp \
			src/Gates/Gate4069.cpp \
			src/Gates/Gate4071.cpp \
			src/Gates/Gate4030.cpp \
			src/Gates/Gate4001.cpp \
			src/Gates/Gate4011.cpp \
			src/Advanced_Gates/Gate4008.cpp

OBJ		=	$(SRC:.cpp=.o)

CC		=	g++

CFLAGS	=	-I./includes

ERRORFLAGS	=	-std=c++20 -Wall -Wextra -Werror

all:	$(NAME)

$(NAME):	$(OBJ)
		$(CC) $(OBJ) -o $(NAME) $(CFLAGS) $(ERRORFLAGS)
		make clean
clean:
	$(RM) $(OBJ)

fclean: clean
	$(RM) $(NAME) unit_tests $(OBJ)

re:	fclean all

.PHONY:	 clean fclean re all
