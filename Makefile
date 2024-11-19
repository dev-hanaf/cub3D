CC = cc
CFLAGS = -Wall -Wextra -Werror -g3 #-fsanitize=address
AR = ar rcs

LIBFT = ./includes/libft
MLX = -lmlx_Linux -lXext -lX11 -lm

SRC = $(wildcard src/*.c)  $(wildcard src/*/*.c) 


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

sup: all
	valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes ./cub3D maps/map1.cub
.SECONDARY : $(OBJ)
