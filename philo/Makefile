CC = gcc
CFLAGS = -Wall -Wextra -Werror

SRCS = src/philo.c

NAME = philo

OBJS = $(SRCS:.c=.o)

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) -o $(NAME) $(OBJS)

clean:
	rm -rf $(OBJS)

fclean:
	rm -rf $(NAME) $(OBJS)

re: fclean all