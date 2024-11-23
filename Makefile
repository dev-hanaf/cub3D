CC = cc
CFLAGS = -Wall -Wextra -Werror
AR = ar rcs

LIBFT = ./includes/libft
MLX = -lmlx_Linux -lXext -lX11 -lm

SRC = src/cub3d.c src/parsing/advanced_atoi.c src/parsing/free.c src/parsing/get_next_line.c\
	src/parsing/get_next_line_utils.c src/parsing/init.c src/parsing/map_builder.c src/parsing/map.c\
	src/parsing/map_parser.c src/parsing/rgb.c src/parsing/rgb_loop.c src/parsing/splite.c\
	src/parsing/utils.c src/raycasting/draw.c src/raycasting/fill_map.c src/raycasting/find_hits.c\
	src/raycasting/init_var.c src/raycasting/moves.c src/raycasting/raycasting.c\
	src/raycasting/wall_projection.c src/utils/utils1.c src/utils/utils.c
 

OBJ = $(SRC:.c=.o)
NAME = cub3D


LIBS = -L$(LIBFT) -lft 

INC = -Iincludes/libft -Iheaders

all:  $(NAME)

$(NAME): $(OBJ)
	@make -C $(LIBFT)
	$(CC) $(CFLAGS)  $(OBJ) $(INC) $(MLX)  $(LIBS) -o $(NAME)

%.o: %.c
	$(CC) $(CFLAGS) $(INC) -c $< -o $@

clean:
	@make clean -C $(LIBFT)
	rm -f $(OBJ)

fclean: clean
	@make fclean -C $(LIBFT)
	rm -f $(NAME)

re: fclean all

.SECONDARY : $(OBJ)
