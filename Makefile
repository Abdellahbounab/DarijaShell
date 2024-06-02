NAME = minishell
CFLAGS = -Wall -Wextra -Werror -lreadline -lncurses 

# all:

# $(NAME): 

# clean:

# fclean:

# re:

TST=	parsing/test.c \
		parsing/split_cmd.c \
		parsing/parsing_tooles.c \
		parsing/meaning.c \
		# exec.c \
		# set_defaults.c 
OTST=$(TST:.c=.o)

all: test

# test: lib $(OTST)
# 	cc -lreadline -lncurses -fsanitize=address -Llibft -lft libft/libft.a $(OTST)

test: lib $(OTST) parsing/parsing.h
	cc $(OTST) -Llibft -lft -lreadline -lncurses -fsanitize=address -o test
	
fclean:
	make fclean -C libft
	rm -f a.out $(OTST)

lib:
	make -C libft
