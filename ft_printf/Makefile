NAME = libftprintf.a

SRCS = ft_puthex.c\
	ft_printf.c\
	ft_putchar.c\
	ft_putnbr.c\
	ft_putstr.c\

OBJS = $(SRCS:.c=.o)

CC = cc

CFLAGS = -Wall -Wextra -Werror

${NAME} : ${OBJS}
	ar rc ${NAME} ${OBJS}

all: ${NAME}

clean: 
	rm -f ${OBJS}

fclean: clean
	rm -f ${NAME}

re: fclean all

.PHONY:	all clean fclean re bonus