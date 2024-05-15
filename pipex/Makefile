CC = cc
CFLAGS = -Wall -Wextra -Werror
CFILES = check_leaks.c parsing_utils.c parsing.c pipex.c pipex_utils.c gnl/get_next_line.c gnl/get_next_line_utils.c
CBONUS = check_leaks.c parsing_utils.c parsing.c pipex_bonus.c pipex_utils.c gnl/get_next_line.c gnl/get_next_line_utils.c
OFILES = $(CFILES:.c=.o)
OBONUS = $(CBONUS:.c=.o)
NAME = pipex
LIBFT = libft.a
PRINTF = libftprintf.a

all: $(PRINTF) $(LIBFT) $(NAME)

$(PRINTF):
	cd ./printf && make
$(LIBFT): 
	cd ./libft && make

$(NAME): $(OFILES)
	$(CC) $(CFLAGS) $(OFILES) ./libft/$(LIBFT) ./printf/$(PRINTF) -o $(NAME)

bonus: $(OBONUS) $(LIBFT) $(PRINTF)
	$(CC) $(CFLAGS) $(OBONUS) ./printf/$(PRINTF) ./libft/$(LIBFT) -o $(NAME)

clean:
	rm -rf $(OFILES) $(OBONUS)
	cd ./libft && make clean
	cd ./printf && make clean

fclean: clean
	rm -rf $(NAME)
	cd ./libft && make fclean
	cd ./printf && make fclean

re: fclean all
