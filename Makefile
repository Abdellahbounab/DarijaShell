NAME = minishell
CFLAGS = -Wall -Wextra -Werror -lreadline -lncurses 

# all:

# $(NAME): 

# clean:

# fclean:

# re:

TST=	parsing/test.c \
		parsing/split_cmd.c \
		parsing/var_tooles.c \
		parsing/parsing.c \
		parsing/filter.c \
		parsing/new_parsing.c \
		# exec.c \
		# set_defaults.c 
OTST=$(TST:.c=.o)

all: test

test: lib
	cc -lreadline -lncurses -fsanitize=address -Llibft libft/libft.a $(TST)

# test: lib $(OTST) parsing/parsing.h
# 	cc $(OTST) -Llibft -lft -lreadline -lncurses -fsanitize=address -o test
	
fclean:
	make fclean -C libft
	rm -f a.out $(OTST)

lib:
	make -C libft
