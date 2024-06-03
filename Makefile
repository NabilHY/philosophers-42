CC = cc
FLAGS = -Wall -Wextra -Werror
INCLUDE = ./philo/philo.h
SRCS = ./philo/philo.c \
./philo/srcs/utils.c \
./philo/srcs/init.c \
./philo/srcs/simulation.c
OBJS = $(SRCS:.c=.o)
NAME = falasifa
ADDRESS = -fsanitize=address
THREAD = -fsanitize=thread

all: $(NAME)

$(NAME): $(OBJS) $(INCLUDE)
	$(CC) $(FLAGS) $(OBJS) -o $(NAME)

clean:
	rm -rf $(OBJS)
fclean: clean
	rm -rf $(NAME)
re: fclean all
.PHONY: PHILO