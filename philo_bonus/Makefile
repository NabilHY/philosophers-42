CC = cc
FLAGS = -Wall -Wextra -Werror
INCLUDE = ./philo_bonus.h
SRCS = ./philo_bonus.c \
./srcs/utils_bonus.c \
./srcs/init_bonus.c \
./srcs/time_bonus.c \
./srcs/simulation_bonus.c \
./srcs/monitor_bonus.c
OBJS = $(SRCS:.c=.o)
NAME = philo_bonus
ADDRESS = -fsanitize=address
THREAD = -fsanitize=thread

all: $(NAME)

$(NAME): $(OBJS) $(INCLUDE)
	$(CC) $(FLAGS) $(OBJS)  -o $(NAME)

clean:
	rm -rf $(OBJS)
fclean: clean
	rm -rf $(NAME)
re: fclean all