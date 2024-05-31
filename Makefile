NAME = minishell
CFLAGS = -Wall -Wextra -Werror -lreadline -lncurses 

# all:

# $(NAME): 

# clean:

# fclean:

# re:

TST=	test.c \
		split_cmd.c \
		exec.c \
		set_defaults.c \
		create_env.c
# OTST=$(TST:.c=.o)

all: test

test: lib
	cc -lreadline -lncurses -fsanitize=address libft/libft.a $(TST)

fclean:
	make fclean -C libft
	rm -f a.out

lib:
	make -C libft
