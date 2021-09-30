NAME = philo

HEADER = philo.h

SOURCE = ft_atoi.c\
			die_and_do.c\
			initialize.c\
			output.c\
			sleep_eat_think.c\
			timesa.c\

OBJS = $(SOURCE:.c=.o)

CFLAGS = -Wall -Wextra -Werror -I.

CC = gcc

RM = rm -rf

all: 		$(NAME)

$(NAME):	$(OBJS) $(HEADER) main.c
			gcc -Wall -Werror -Wextra main.c $(OBJS) -o philo

clean:
		$(RM) $(OBJS)

fclean: clean
		$(RM) philo

re:		fclean all

.PHONY: all clean fclean re

