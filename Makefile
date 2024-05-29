CC = cc
FLAGS = -Wall -Wextra -Werror
INCLUDE = ./philo/philo.h
SRCS = ./philo/philo.c \
./philo/srcs/utils.c \
./philo/srcs/init.c
OBJS = $(SRCS:.c=.o)
NAME = falasifa
FSANITIZE = -fsanitize=address

all: $(NAME)

$(NAME): $(OBJS) $(INCLUDE)
	$(CC) $(FLAGS) -I$(INCLUDE) $(FSANITIZE) $(OBJS) -o $(NAME)

clean:
	rm -rf $(OBJS)
fclean: clean
	rm -rf $(NAME)
re: fclean all
.PHONY: PHILO