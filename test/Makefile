NAME	=	test

SRC	=	main.cpp		\
		src/IOManager.cpp	\
		src/Logger.cpp


OBJ	=	$(SRC:.cpp=.o)

RM	=	rm -rf

CC	=	g++

CPPFLAGS	=	-Iinclude -g -std=c++11

$(NAME):	$(OBJ)
		$(CC) $(OBJ) -o $(NAME) -g

all:		$(NAME)

clean:
		$(RM) $(OBJ)

fclean:		clean
		$(RM) $(NAME)

re: fclean all
