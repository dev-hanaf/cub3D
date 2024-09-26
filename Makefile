CC = cc
CFLAGS = -Wall -Wextra -Werror
AR = ar rcs

SRC = $(wildcard src/*.c)


OBJ = $(SRC:.c=.o)
#MLX = -lmlx_Linux -lXext -lX11
MLX =
NAME = cub3D

all:  $(NAME)

$(NAME): $(OBJ)
	$(CC) $(CFLAGS) $(MLX) $(OBJ)  -o $(NAME)

%.o: %.c
	$(CC) $(CFLAGS) -I./headers -c $< -o $@

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean all

.SECONDARY : $(OBJ)