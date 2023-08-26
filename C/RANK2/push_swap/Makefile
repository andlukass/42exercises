GREEN := \033[32m
RED := \033[31m
END := \033[0m

CFLAGS = #-Wall -Wextra -Werror

SRCS = main.c \
	utils/ft_atoi.c utils/is_number.c stack/stack.c \
	movements/swap.c movements/push.c movements/rotate.c \
	movements/reverse_rotate.c utils/bubble_sort.c \
	sorting/sort_little.c  sorting/sort_large.c \
	utils/ft_strdup.c sorting/is_sorted.c \
	sorting/sort_three.c

OBJS = $(SRCS:.c=.o)

NAME = push_swap

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	@rm -rf $(OBJS)
	@echo "\n$(RED)> Cleaned! 🗑️\n$(END)"

fclean:
	@rm -rf $(NAME) $(OBJS)
	@echo "\n$(RED)> All cleaned! 🗑️\n$(END)"

re: clean all