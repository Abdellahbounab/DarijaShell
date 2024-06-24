NAME = minishell_bonus
CFLAGS = -Wall -Wextra -Werror -g

#  -fsanitize=address
SRC =	main_bonus.c \
		parsing_bonus/cmd_bonus.c \
		parsing_bonus/free_bonus.c \
		parsing_bonus/new_filter_bonus.c \
		parsing_bonus/new_parsing_bonus.c \
		parsing_bonus/parsing_tooles_bonus.c \
		parsing_bonus/split_line_bonus.c 	\
		parsing_bonus/var_tooles_bonus.c \
		# env/built_in.c\
		# env/create_env.c 

INCLUDES=	parsing_bonus/parsing_bonus.h\
			types_bonus.h \
			# env/env.h \

OBJ=$(SRC:.c=.o)

%.o: %.c $(INCLUDES)
	cc $(CFLAGS) -c $< -o $@

all: $(NAME)

$(NAME): $(OBJ) 
	make -C ../libft
	cc $(CFLAGS) -lreadline -lncurses $(OBJ) ../libft/libft.a -o $@

clean: 
	make clean -C ../libft
	rm -f $(OBJ)

fclean: clean
	make fclean -C ../libft
	rm -f $(NAME)

re: fclean all 
