CC = cc -fsanitize=address -g3 #-L./minilibx_linux -fsanitize=address 
CFLAGS = -Wall -Wextra -Werror	-Ofast
AR = ar rcs

GET_NEXT_LINE = ./includes/get_next_line
LIBFT = ./includes/libft
GARBAGE = ./includes/gc
GNL = includes/get_next_line
MLX = -lmlx_Linux -lXext -lX11 -lm
#MLX = -Lmlx -lmlx -framework OpenGL -framework AppKit

SRC = $(wildcard src/*.c) $(GET_NEXT_LINE)/get_next_line_utils.c $(GET_NEXT_LINE)/get_next_line.c


OBJ = $(SRC:.c=.o)
NAME = cub3D


LIBS = -L$(LIBFT) -lft -L$(GARBAGE) -lgarbage

INC = -Iincludes/libft -Iincludes/gc -Iheaders

all:  $(NAME)

$(NAME): $(OBJ)
	@make -C $(GARBAGE)
	@make -C $(LIBFT)
	$(CC) $(CFLAGS)  $(OBJ) $(INC)  $(MLX) -o $(NAME)

%.o: %.c
	$(CC) $(CFLAGS) $(INC)  -Imlx -c $< -o $@

clean:
	@make clean -C $(LIBFT)
	@make clean -C $(GARBAGE)
	rm -f $(OBJ)

fclean: clean
	@make fclean -C $(LIBFT)
	@make fclean -C $(GARBAGE)
	rm -f $(NAME)

re: fclean all

.SECONDARY : $(OBJ)
