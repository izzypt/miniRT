SRCS			=	ft_printf.c ft_putaddress.c ft_putchar.c ft_puthex.c \
					ft_putnbr.c ft_putstr.c ft_strlen.c ft_putnbru.c

OBJS			= $(SRCS:.c=.o)


CC				= cc
RM				= rm -f
CFLAGS			= -Wall -Wextra -Werror

NAME			= printf.a

all:			$(NAME)

$(NAME):		$(OBJS)
				ar rcs $(NAME) $(OBJS)

clean:
				$(RM) $(OBJS) $(NAME)

fclean:			clean
					$(RM) $(NAME)

re:					fclean $(NAME)

.PHONY:			all clean fclean re