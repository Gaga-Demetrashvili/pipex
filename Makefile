NAME = pipex

LIBFT_DIR = libft
LIBFT_MAKE = make -C $(LIBFT_DIR)
LIBFT_A = $(LIBFT_DIR)/libft.a

FT_PRINTF_DIR = ft_printf
FT_PRINTF_MAKE = make -C $(FT_PRINTF_DIR)
FT_PRINTF_A = $(FT_PRINTF_DIR)/libftprintf.a

SRC = mandatory/pipex.c\
	mandatory/utils.c\
	mandatory/cleanup.c\
	mandatory/find_path_utils.c

OBJ = $(SRC:.c=.o)

CC = cc
CFLAGS = -Wall -Wextra -Werror

all: $(LIBFT_A) $(FT_PRINTF_A) $(NAME)

$(NAME): $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) $(LIBFT_A) $(FT_PRINTF_A) -o $(NAME)

$(LIBFT_A):
	$(LIBFT_MAKE)

$(FT_PRINTF_A):
	$(FT_PRINTF_MAKE)

clean:
	rm -f $(OBJ)
	make clean -C $(LIBFT_DIR)
	make clean -C $(FT_PRINTF_DIR)

fclean: clean
	rm -f $(NAME)
	rm -f $(LIBFT_A)
	rm -f $(FT_PRINTF_A)

re: fclean all

.PHONY: all clean fclean re bonus





































