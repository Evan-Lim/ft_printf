NAME        = libftprintf.a
LIBFT_DIR   = libft
LIBFT       = $(LIBFT_DIR)/libft.a
CC          = cc
CFLAGS      = -Wall -Wextra -Werror
INCLUDES    = -I. -I$(LIBFT_DIR)

SRCS = ft_printf.c \
       ft_printf_parser.c \
       ft_printf_text.c \
       ft_printf_num.c \
       ft_printf_num_utils.c \
       ft_printf_utils.c \
       ft_printf_base.c

OBJS = $(SRCS:.c=.o)

all: $(NAME)

$(NAME): $(OBJS) $(LIBFT)
	ar rcs $(NAME) $(OBJS) $(LIBFT_DIR)/*.o

$(LIBFT):
	make -C $(LIBFT_DIR)

%.o: %.c ft_printf.h
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

clean:
	rm -f $(OBJS)
	make -C $(LIBFT_DIR) clean

fclean: clean
	rm -f $(NAME)
	make -C $(LIBFT_DIR) fclean

re: fclean all

.PHONY: all clean fclean re