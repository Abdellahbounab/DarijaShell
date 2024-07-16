NAME = minishell
CFLAGS = -Wall -Wextra -Werror
#-fsanitize=address -g
LDFLAGS := -lreadline -lncurses

SRC =	parsing/cmd.c \
		parsing/free.c \
		parsing/new_filter.c \
		parsing/parsing.c \
		parsing/parsing_tooles.c \
		parsing/split_line.c 	\
		parsing/var_tooles.c \
		parsing/files.c \
		parsing/wildcards.c \
		parsing/sort.c \
		parsing/match.c \
		parsing/parsing_split.c \
		parsing/create_file.c \
		parsing/heredoc_var.c \
		getnextline/get_next_line_bonus.c\
		env/built_in_1.c \
		env/built_in_2.c \
		env/built_in_3.c \
		env/create_env.c \
		env/env_built_in.c 


INCLUDES =	env/env.h parsing/parsing.h excution/excution.h types.h \
			getnextline/get_next_line_bonus.h 

LIBFT_DIR := libft
LIBFT := $(LIBFT_DIR)/libft.a

OBJ=$(SRC:.c=.o)

RDLINE_SRCS =	excution/main_excution.c \
				excution/excution_herdoc.c \
				excution/excution_cmd_1.c \
				excution/excution_cmd_2.c \
				excution/excution_files.c \
				excution/excution_signal.c \
				excution/excution_tooles.c \
				main.c

RDLINE =  /goinfre/$(shell users)/homebrew/opt/readline

RDLINE_OBJS=$(RDLINE_SRCS:.c=.o)

BOLD := \033[1m
CYAN := \033[36m
YELLOW := \033[33m
ORG := \033[34;1m
RED := \033[31;1m
MAGENTA := \033[35m
GREEN := \033[32m
RESET := \033[0m

define MINISHELL_LOGO
$(BOLD)$(CYAN)
 __  __ _       _     _          _ _ 
|  \/  (_)     (_)   | |        | | |
| \  / |_ _ __  _ ___| |__   ___| | |
| |\/| | | '_ \| / __| '_ \ / _ \ | |
| |  | | | | | | \__ \ | | |  __/ | |
|_|  |_|_|_| |_|_|___/_| |_|\___|_|_|

$(YELLOW)╔═══════════════════════════════════╗$(CYAN)
$(YELLOW)║$(RESET)	$(MAGENTA)achakkaf$(RESET)$(GREEN) && $(RESET)$(MAGENTA)abounab$(RESET)	$(YELLOW)    ║$(CYAN)
$(YELLOW)╚═══════════════════════════════════╝$(RESET)                                                     
endef
export MINISHELL_LOGO

all: print_logo $(NAME)

print_logo:
	@echo "$$MINISHELL_LOGO"
	@echo "$(CYAN)$(BOLD)Building Minishell...$(RESET)"

$(NAME): $(OBJ) $(LIBFT) $(RDLINE_OBJS)
	@echo "$(ORG)╔══ Linking object files ══╗$(RESET)"
	@echo "$(CYAN)➜ Creating executable: $(BOLD)$(NAME)$(RESET)"
# @cc $(CFLAGS) $(RDLINE_OBJS) $(OBJ) $(LIBFT) -o $@ $(LDFLAGS)
	@cc $(CFLAGS) -L $(RDLINE)/lib $(RDLINE_OBJS) $(OBJ) $(LIBFT) -o $@ $(LDFLAGS)
	@echo "$(GREEN)✔ Build successful: $(BOLD)$(NAME) is ready!$(RESET)"
	@echo "$(ORG)╚══════════════════════════╝$(RESET)"

%.o: %.c $(INCLUDES)
	@echo "$(YELLOW)➜ Compiling: $(BOLD)$<$(RESET)"
	@$(CC) $(CFLAGS) -c $< -o $@
	@echo "$(GREEN)✔ Object file created: $(BOLD)$@$(RESET)"

$(LIBFT):
	@echo "$(MAGENTA)╔══════ Building libft ══════╗$(RESET)"
	@make -C $(LIBFT_DIR)
	@echo "$(MAGENTA)╚════════════════════════════╝$(RESET)"

clean:
	@echo "$(RED)╔════ Cleaning up ════╗$(RESET)"
	@make -C $(LIBFT_DIR) clean
	@rm -f $(OBJ)
	@rm -f $(RDLINE_OBJS)
	@echo "$(YELLOW)$(BOLD)➜ Removed object files$(RESET)"
	@echo "$(GREEN)$(BOLD)✔ Clean complete$(RESET)"
	@echo "$(RED)╚═════════════════════╝$(RESET)"

fclean: clean
	@echo "$(RED)╔═══ Deep cleaning ═══╗$(RESET)"
	@make -C $(LIBFT_DIR) fclean
	@rm -f $(NAME)
	@echo "$(YELLOW)$(BOLD)➜ Removed $(BOLD)$(NAME)$(RESET)"
	@echo "$(GREEN)$(BOLD)✔ Full clean complete$(RESET)"
	@echo "$(RED)╚═════════════════════╝$(RESET)"


$(RDLINE_OBJS):%.o: %.c $(INCLUDES) $(RDLINE)
	@cc $(CFLAGS) -I $(RDLINE)/include -c $< -o $@ 

# $(RDLINE_OBJS):%.o: %.c $(INCLUDES)
# @cc $(CFLAGS) -c $< -o $@ 

$(RDLINE) :
	@brew install readline

run : 
	@./$(NAME)

readline : $(RDLINE)

re: fclean readline all

