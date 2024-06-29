NAME = minishell
CFLAGS = -Wall -Wextra -Werror

# -L ./goinfre/abounab/homebrew/Cellar/readline/8.2.10/lib -I ./goinfre/abounab/homebrew/Cellar/readline/8.2.10:/include

#  -fsanitize=address -g
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
		getnextline/get_next_line_bonus.c\
		env/built_in.c

INCLUDES=	env/env.h \
			parsing/parsing.h\
			types.h

RDLINE_NAME = readline

# RDLINE = -L ./$(RDLINE_NAME) -I./$(RDLINE_NAME) -lreadline -lncurses
RDLINE = -lreadline -lncurses

OBJ=$(SRC:.c=.o)

%.o: %.c $(INCLUDES)
	cc $(CFLAGS) -c $< -o $@

# all: $(RDLINE_NAME) $(NAME)
all: $(NAME)

$(NAME): $(OBJ) 
	make -C libft
	cc $(CFLAGS)  $(OBJ) libft/libft.a -o $@ $(RDLINE)
#  cc $(CFLAGS) $(pkg-config --cflags --libs readline) -lreadline -lncurses $(OBJ) libft/libft.a -o $@ 

ireadline :
	@brew install $(RDLINE_NAME)
	mv /goinfre/abounab/homebrew/Cellar/readline/8.2.10 readline
	cd $(RDLINE_NAME) && ./configure > /dev/null 2>&1
	echo "compiling readline"

$(RDLINE_NAME) :
	 		make -C $(RDLINE_NAME) > /dev/null 2>&1

clean:
	make clean -C libft
	rm -f $(OBJ)

fclean: clean
	make fclean -C libft
	rm -rf $(RDLINE_NAME)
	rm -f $(NAME)

re: fclean ireadline all
