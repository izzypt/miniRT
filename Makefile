NAME=miniRT
CFLAGS=-Wall
CC=cc
SRC=src/main.c inc/libs/get_next_line/get_next_line.c src/objects.c src/vectors.c src/intersections.c \
	src/canvas.c src/maths.c src/init.c src/colors.c src/reflections.c

MLX_LIB=inc/libs/mlx_linux/libmlx.a

LIBFT_LIB=inc/libs/Libft_SB/libft.a

PRINTF_LIB=inc/libs/printf/printf.a

LDFLAGS= $(PRINTF_LIB) $(LIBFT_LIB) $(MLX_LIB) -lXext -lX11 -lm -lz -g -fsanitize=address

all : $(NAME)

$(NAME) : $(SRC) $(MLX_LIB) $(LIBFT_LIB) $(PRINTF_LIB)
	$(CC) $(SRC) -o $(NAME) $(CFLAGS) $(LDFLAGS)

$(MLX_LIB):
	cd inc/libs/mlx_linux && make
	cd ..

$(LIBFT_LIB):
	cd inc/libs/Libft_SB && make
	cd ..

$(PRINTF_LIB):
	cd inc/libs/printf && make
	cd ..

clean:
	rm -f $(NAME)
	make -C inc/libs/Libft_SB clean
	make -C inc/libs/mlx_linux clean
	make -C inc/libs/printf clean

fclean:		clean
		rm -rf $(NAME)

valgrind:	re
	valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes --track-fds=yes --log-file=valgrind-out.txt

re:			fclean all

.PHONY: all clean fclean re
