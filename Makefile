NAME=miniRT
CFLAGS=-Wall
CC=cc
SRC=src/main.c \
	inc/libs/get_next_line/get_next_line.c \
	src/utils/getters.c src/utils/vectors.c src/utils/canvas.c src/utils/maths.c  src/utils/colors.c  src/utils/free.c src/utils/errors.c \
	src/parser/file_parse.c src/parser/parse_elements.c src/parser/parse_shapes.c src/parser/validators.c\
	src/renderer/intersections.c src/renderer/reflections.c src/renderer/render.c src/renderer/hooks.c src/renderer/sphere.c src/renderer/plane.c src/renderer/cylinder.c\
	src/initializer/initial_values.c src/initializer/light.c src/initializer/plane.c src/initializer/sphere.c src/initializer/cylinder.c\
	src/utils/ft_atoi.c \

MLX_LIB=inc/libs/mlx_linux/libmlx.a

LIBFT_LIB=inc/libs/Libft_SB/libft.a

PRINTF_LIB=inc/libs/printf/printf.a

LDFLAGS= $(PRINTF_LIB) $(MLX_LIB) -L/usr/X11/lib -lXext -lX11 -lm -lz -g -fsanitize=address

all : $(NAME)

$(NAME) : $(SRC) $(MLX_LIB) $(PRINTF_LIB)
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
	make -C inc/libs/mlx_linux clean
	make -C inc/libs/printf clean

fclean:		clean
		rm -rf $(NAME)

valgrind:	re
	valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes --track-fds=yes --log-file=valgrind-out.txt

re:			fclean all

.PHONY: all clean fclean re
