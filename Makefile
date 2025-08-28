NAME = pipex

LIBFT_DIR = libft
LIBFT_MAKE = make -C $(LIBFT_DIR)
LIBFT_A = $(LIBFT_DIR)/libft.a

FT_PRINTF_DIR = ft_printf
FT_PRINTF_MAKE = make -C $(FT_PRINTF_DIR)
FT_PRINTF_A = $(FT_PRINTF_DIR)/libftprintf.a

SRC = mandatory/pipex.c\
	mandatory/validations.c\
	cleanup.c\
	utils.c\
	find_path_utils.c

SRC_B = bonus/pipex_b.c\
	bonus/validations_b.c\
	bonus/get_next_line.c\
	bonus/get_next_line_utils.c\
	cleanup.c\
	utils.c\
	find_path_utils.c

OBJ = $(SRC:.c=.o)

OBJ_B = $(SRC_B:.c=.o)

CC = cc
CFLAGS = -Wall -Wextra -Werror -g

all: $(LIBFT_A) $(FT_PRINTF_A) $(NAME)

# $(NAME): $(OBJ)
# 	$(CC) $(CFLAGS) $(OBJ) $(LIBFT_A) $(FT_PRINTF_A) -o $(NAME)

$(NAME): $(OBJ_B)
	$(CC) $(CFLAGS) $(OBJ_B) $(LIBFT_A) $(FT_PRINTF_A) -o $(NAME)

$(LIBFT_A):
	$(LIBFT_MAKE)

$(FT_PRINTF_A):
	$(FT_PRINTF_MAKE)

$(OBJ_B): $(LIBFT_A) $(FT_PRINTF_A)

bonus: $(OBJ_B)
	$(CC) $(CFLAGS) $(OBJ_B) $(LIBFT_A) $(FT_PRINTF_A) -o $(NAME)

clean:
	rm -f $(OBJ) $(OBJ_B)
	make clean -C $(LIBFT_DIR)
	make clean -C $(FT_PRINTF_DIR)

fclean: clean
	rm -f $(NAME)
	rm -f $(LIBFT_A)
	rm -f $(FT_PRINTF_A)

re: fclean all

.PHONY: all clean fclean re bonus


