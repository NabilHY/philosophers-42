CC = cc
FLAGS = -Wall -Wextra -Werror
INCLUDE = ./philo/philo.h
SRCS = ./philo/philo.c \
./philo/srcs/utils.c \
./philo/srcs/init.c \
./philo/srcs/simulation.c \
./philo/srcs/time.c \
./philo/srcs/monitor.c
OBJS = $(SRCS:.c=.o)
NAME = philo
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