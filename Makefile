NAME = philo

CC = gcc

CFLAGS = -Wall -Wextra -Werror -pthread

HDR = philo.h

SRC = main.c iniz.c philo.c living_in_a_simulation.c life_philosophy.c checking.c freadom.c  philosophical_letters.c

OBJ = $(SRC:.c=.o)

RM = rm -f


$(NAME): $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) -o $(NAME)

%.o: %.c $(HDR)
	$(CC) $(CFLAGS) -c $< -o $@


all: $(NAME)

re:	fclean
	make all

clean:
	${RM} $(OBJ)

fclean: clean
	${RM} $(NAME) ${OBJ}




.PHONY: all bonus clean fclean re clear rebonus