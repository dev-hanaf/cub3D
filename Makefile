CC = cc
CFLAGS = -Wall -Wextra -Werror -g3 #-fsanitize=address 
AR = ar rcs

GET_NEXT_LINE = ./includes/get_next_line
LIBFT = ./includes/libft
GARBAGE = ./includes/gc
MLX = -lmlx_Linux -lXext -lX11

SRC = $(wildcard src/*.c)  $(wildcard src/*/*.c)


OBJ = $(SRC:.c=.o)
NAME = cub3D


LIBS = -L$(LIBFT) -lft -L$(GARBAGE) -lgarbage

INC = -Iincludes/libft -Iincludes/gc -Iheaders

all:  $(NAME)

$(NAME): $(OBJ)
	@make -C $(GARBAGE)
	@make -C $(LIBFT)
	$(CC) $(CFLAGS)  $(OBJ) $(INC) $(MLX)  $(LIBS) -o $(NAME)

%.o: %.c
	$(CC) $(CFLAGS) $(INC) -c $< -o $@

clean:
	@make clean -C $(LIBFT)
	@make clean -C $(GARBAGE)
	rm -f $(OBJ)

fclean: clean
	@make fclean -C $(LIBFT)
	@make fclean -C $(GARBAGE)
	rm -f $(NAME)

re: fclean all

sup: all
	valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes ./cub3D maps/test.cub
.SECONDARY : $(OBJ)
