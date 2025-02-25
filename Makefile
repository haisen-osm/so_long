NAME = so_long
SRCS = helpers/ft_strchr.c helpers/ft_strcmp.c helpers/ft_putchar.c helpers/ft_putnbr.c helpers/ft_putstr.c helpers/ft_strcpy.c helpers/ft_strdup.c helpers/ft_strjoin.c helpers/ft_strlen.c helpers/get_next_line.c main.c
OBJS = $(SRCS:.c=.o)
CC = cc
CFLAGS = -Wall -Wextra -Werror -g -fsanitize=address

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -L./minilibx-linux -lmlx -lX11 -lXext -o $(NAME)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -rf $(OBJS)

fclean: clean
	rm -rf $(NAME)

re: fclean all

.PHONY: all clean fclean re
.SECONDARY:$(OBJS)
