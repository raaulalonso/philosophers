CC = gcc
CFLAGS = -Wall -Wextra #-Werror
PTHREAD = -lpthread

NAME = philo

SRCS = src/philo.c src/utils.c src/init.c
OBJS = $(SRCS:.c=.o)

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) -o $(NAME) $(OBJS) $(PTHREAD)

clean:
	rm -rf $(OBJS)

fclean:
	rm -rf $(NAME) $(OBJS)

re: fclean all