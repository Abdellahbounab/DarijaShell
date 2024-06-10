NAME = minishell
CFLAGS = -Wall -Wextra -Werror -lreadline -lncurses 

# all:

# $(NAME): 

# clean:

# fclean:

# re:

TST=	parsing/cmd.c \
		parsing/free.c \
		parsing/new_filter.c \
		parsing/new_parsing.c \
		parsing/parsing_tooles.c \
		parsing/split_line.c 	\
		parsing/test.c \
		parsing/var_tooles.c 
	
OTST=$(TST:.c=.o)

all: test

test: lib
	cc -lreadline -lncurses  -Llibft libft/libft.a $(TST)

# test: lib $(OTST) parsing/parsing.h-fsanitize=address
# 	cc $(OTST) -Llibft -lft -lreadline -lncurses -fsanitize=address -o test
	
fclean:
	make fclean -C libft
	rm -f a.out $(OTST)

lib:
	make -C libft
