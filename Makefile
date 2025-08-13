CC = cc
CFLAGS =  -Wall -Wextra -Werror
SRCS = main.c init_simulation.c monitor_philo.c philos_simulation.c utils.c actions.c cleanup.c init_mutexes.c time_utils.c thread_utils.c parse_utils.c
OBJDIR = objs
OBJS = $(SRCS:%.c=$(OBJDIR)/%.o)
NAME = philo

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) -o $(NAME) $(OBJS)

$(OBJDIR)/%.o: %.c
	mkdir -p $(OBJDIR)
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -rf $(OBJDIR)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
