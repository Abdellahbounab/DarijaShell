NAME = minishell
CFLAGS = -Wall -Wextra -Werror -lreadline -lncurses 

# all:

# $(NAME): 

# clean:

# fclean:

# re:

TST=	parsing/test.c \
		parsing/split_cmd.c \
		# exec.c \
		# set_defaults.c 
# OTST=$(TST:.c=.o)   -fsanitize=address

all: test

test: lib
	cc -lreadline -lncurses  libft/libft.a $(TST)

fclean:
	make fclean -C libft
	rm -f a.out

lib:
	make -C libft
