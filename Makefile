NAME = fdf
SRC = fdf.c \
      draw.c \
      read.c \
      hook.c \
      tools.c
OBJ = $(SRC:.c=.o)
MLX = .minilibx
LIBFT = Libft
LIBFT_A = $(LIBFT)/libft.a
FLAGS = -fsanitize=address -g3 -Wall -Wextra -Werror
LIBS = -L$(MLX) -lmlx -L$(LIBFT) -lft -lXext -lX11

all: $(LIBFT_A) $(NAME)

$(LIBFT_A):
	$(MAKE) -C $(LIBFT)

$(NAME): $(LIBFT_A) $(OBJ)
	$(CC) $(FLAGS) -I$(MLX) -I$(LIBFT) $(OBJ) -o $@ $(LIBS)

%.o: %.c $(LIBFT_A)
	$(CC) $(FLAGS) -I$(MLX) -I$(LIBFT) -c $< -o $@

clean:
	rm -f $(OBJ)
	$(MAKE) -C $(LIBFT) clean

fclean: clean
	rm -f $(NAME)
	$(MAKE) -C $(LIBFT) fclean

re: fclean all

.PHONY: all clean fclean re
