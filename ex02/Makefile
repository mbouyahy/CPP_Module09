SRCS =	PmergeMe.cpp main.cpp

OBJS =	${SRCS:.cpp=.o}

NAME =	PmergeMe

RM =	rm -f

CC =	c++

FLAGS =	-Wall -Wextra -Werror -std=c++98 

%.o: %.cpp PmergeMe.hpp
	${CC} ${FLAGS} -c $< -o $@

${NAME}: ${OBJS}
		 ${CC} -o ${NAME} ${OBJS} ${FLAGS}

all: ${NAME}

clean:
		${RM} ${OBJS}

fclean: clean
		${RM} ${NAME}

re: fclean all

.PHONY: all clean fclean re