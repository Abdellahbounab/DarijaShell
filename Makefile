NAME = minishell
CFLAGS = -Wall -Wextra -Werror

# -L ./goinfre/abounab/homebrew/Cellar/readline/8.2.10/lib -I ./goinfre/abounab/homebrew/Cellar/readline/8.2.10:/include

#  -fsanitize=address -g
SRC =	parsing/cmd.c \
		parsing/free.c \
		parsing/new_filter.c \
		parsing/new_parsing.c \
		parsing/parsing_tooles.c \
		parsing/split_line.c 	\
		parsing/var_tooles.c \
		env/create_env.c \
		getnextline/get_next_line_bonus.c\
		env/built_in.c

INCLUDES =	env/env.h \
			parsing/parsing.h\
			types.h

RDLINE_SRCS = excution/main_excution.c\
			main.c

RDLINE =  -I /goinfre/abounab/homebrew/opt/readline/include 

OBJ=$(SRC:.c=.o)

RDLINE_OBJS=$(RDLINE_SRCS:.c=.o)

%.o: %.c $(INCLUDES)
	cc $(CFLAGS) -c $< -o $@

all: $(NAME)

$(NAME): $(OBJ) $(RDLINE_OBJS)
	make -C libft
	cc $(CFLAGS) -L /goinfre/abounab/homebrew/opt/readline/lib $(RDLINE_OBJS) $(OBJ) libft/libft.a -o $@ -lreadline -lncurses


$(RDLINE_OBJS):%.o: %.c $(INCLUDES)
	cc $(CFLAGS) $(RDLINE) -c $< -o $@ 

clean:
	make clean -C libft
	rm -f $(OBJ)
	rm -f $(RDLINE_OBJS)

fclean: clean
	make fclean -C libft
	rm -f $(NAME)

re: fclean all
