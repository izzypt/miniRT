SRCS			=	ft_bzero ft_isalnum ft_isalpha ft_isascii ft_isdigit ft_isprint ft_putchar_fd ft_putstr_fd ft_putendl_fd \
					ft_memchr ft_memcmp ft_memcpy ft_memmove ft_memset ft_itoa ft_strmapi ft_striteri ft_putnbr_fd \
					ft_strchr ft_strdup ft_calloc ft_substr ft_atoi ft_strjoin ft_strtrim ft_split ft_lstadd_back \
					ft_strlcat ft_strlcpy ft_strlen ft_strncmp ft_strnstr ft_strrchr ft_tolower ft_toupper \

BSRCS 			= 	ft_lstnew ft_lstlast ft_lstsize ft_lstadd_back ft_lstadd_front ft_lstdelone ft_lstiter ft_lstclear ft_lstmap \

OBJS			= $(SRCS:=.o)
BOBJS			= $(BSRCS:=.o)

CC				= cc
RM				= rm -f
CFLAGS			= -Wall -Wextra -Werror

NAME			= libft.a

all:			$(NAME)

$(NAME):		$(OBJS)
				ar rcs $(NAME) $(OBJS)

bonus: 			$(OBJS) $(BOBJS)
				ar rc $(NAME) $(OBJS) $(BOBJS)

clean:
				$(RM) $(OBJS) $(BOBJS) $(NAME)

fclean:			clean
					$(RM) $(NAME)

re:					fclean $(NAME)

.PHONY:			all clean fclean re