NAME		= philo

SRCS		= main.c actions_utils.c dinner.c eating_utils.c \
			init.c monitor.c utils.c utils2.c

OBJS		= $(patsubst %.c, %.o, $(SRCS))

CC			= cc
CFLAGS		= -Wall -Wextra -Werror -pthread -g #-pthread
RM = rm -f

# Compilation rule for the program
$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME)

# Rule to compile object files
%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

all:		$(NAME)

clean:
			$(RM) $(OBJS)


fclean:		clean
			$(RM) $(NAME)

re:			fclean all

rec:		clean all

test:
			./$(NAME) 2 800 200 200 5


.PHONY:		all clean fclean re rec test
