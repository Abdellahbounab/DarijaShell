NAME = minishell
CFLAGS = -Wall -Wextra -Werror -g

#  -fsanitize=address
SRC =	main.c \
		parsing/cmd.c \
		parsing/free.c \
		parsing/new_filter.c \
		parsing/new_parsing.c \
		parsing/parsing_tooles.c \
		parsing/split_line.c 	\
		parsing/var_tooles.c \
		env/create_env.c \
		excution/main_excution.c\
		getnextline/get_next_line_bonus.c
		# env/built_in.c

INCLUDES=	env/env.h \
			parsing/parsing.h\
			types.h 

OBJ=$(SRC:.c=.o)

%.o: %.c $(INCLUDES)
	cc $(CFLAGS) -c $< -o $@

all: $(NAME)

$(NAME): $(OBJ) 
	make -C libft
	cc $(CFLAGS) -lreadline -lncurses $(OBJ) libft/libft.a -o $@ -fsanitize=address -g

clean: 
	make clean -C libft
	rm -f $(OBJ)

fclean: clean
	make fclean -C libft
	rm -f $(NAME)

re: fclean all 
