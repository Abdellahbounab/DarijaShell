NAME = minishell
CFLAGS = -Wall -Wextra -Werror -lreadline -lncurses 

# all:

# $(NAME): 

# clean:

# fclean:

# re:

TST= test.c split_cmd.c exec.c
# OTST=$(TST:.c=.o)

all: test

test: lib
	cc $(CFLAGS) mylib/mylib.a $(TST)

fclean:
	make fclean -C mylib
	rm -f a.out

lib:
	make -C mylib
