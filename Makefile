NAME = fdf
SRC = fdf.c \
	  draw/draw.c \
	  draw/draw2.c \
	  read.c \
	  hook/hook.c \
	  tools.c
OBJ = $(SRC:.c=.o)
MLX = .minilibx
LIBFT = Libft
FLAGS = -fsanitize=address -g3 #-Wall -Wextra -Werror
LIBS = -L$(MLX) -lmlx -L$(LIBFT) -lft -lXext -lX11

all: $(LIBFT) $(NAME)

$(LIBFT):
	$(MAKE) -C $(LIBFT)

$(NAME): $(LIBFT) $(OBJ)
	$(CC) $(FLAGS) -I$(MLX) -I$(LIBFT) $(OBJ) -o $@ $(LIBS)

%.o: %.c $(LIBFT)
	$(CC) $(FLAGS) -I$(MLX) -I$(LIBFT) -c $< -o $@

clean:
	rm -f $(OBJ)
	$(MAKE) -C $(LIBFT) clean

fclean: clean
	rm -f $(NAME)
	$(MAKE) -C $(LIBFT) fclean

re: fclean all

.PHONY: all clean fclean re

