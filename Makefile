NAME = philo
CC = cc
CFLAGS = -Wall -Wextra -Werror
SRCS = philo.c main.c utils.c utils2.c safety.c init.c parsing.c monitor.c dinner.c getters_setters.c write.c
OBJS = $(SRCS:.c=.o)

all: $(NAME)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) -o $(NAME) $(OBJS) -lpthread

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all
