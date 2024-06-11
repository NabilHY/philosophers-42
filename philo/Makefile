CC = cc
FLAGS = -Wall -Wextra -Werror
INCLUDE = ./philo.h
SRCS = ./philo.c \
./srcs/utils.c \
./srcs/init.c \
./srcs/simulation.c \
./srcs/time.c \
./srcs/monitor.c
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