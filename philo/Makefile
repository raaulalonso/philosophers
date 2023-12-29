CC = gcc
CFLAGS = -Wall -Wextra -Werror
PTHREAD = -lpthread

NAME = philo

SRCS = src/philo.c src/args_check.c src/init.c src/getset.c src/sim_utils.c src/time.c
OBJS = $(SRCS:.c=.o)

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) -o $(NAME) $(OBJS) $(PTHREAD)

clean:
	rm -rf $(OBJS)

fclean:
	rm -rf $(NAME) $(OBJS)

re: fclean all
