
NAME := minishell_bonus
CC := cc
CFLAGS := -g -fsanitize=address
# -Wall -Wextra -Werror 
LDFLAGS := -lreadline -lncurses

BOLD := \033[1m
GREEN := \033[32;1m
RED := \033[31;1m
YELLOW := \033[33;1m
ORG := \033[34;1m
MAGENTA := \033[35;1m
CYAN := \033[36;1m
RESET := \033[0m

SRC := main_bonus.c \
       parsing/cmd_bonus.c \
       parsing/free_bonus.c \
       parsing/new_filter_bonus.c \
       parsing/parsing_bonus.c \
       parsing/parsing_tooles_bonus.c \
       parsing/split_line_bonus.c \
       parsing/var_tooles_bonus.c \
       parsing/wildcards_bonus.c \
	#    env/create_env.c \
	#    getnextline/get_next_line_bonus.c\
	#    env/built_in.c

INCLUDES =	parsing/parsing_bonus.h\
			types_bonus.h \
			# env/env.h 

OBJ := $(SRC:.c=.o)

# RDLINE_SRCS = excution/main_excution.c\
			# main.c

# RDLINE =  /goinfre/$(shell users)/homebrew/opt/readline

# RDLINE_OBJS=$(RDLINE_SRCS:.c=.o)

LIBFT_DIR := ../libft
LIBFT := $(LIBFT_DIR)/libft.a

.PHONY: all clean fclean re

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
	@echo "$(CYAN)Building Minishell...$(RESET)"

$(NAME): $(OBJ) $(LIBFT) $(RDLINE_OBJS)
	@echo "$(ORG)╔══ Linking object files ══╗$(RESET)"
	@echo "$(CYAN)➜ Creating executable: $(BOLD)$(NAME)$(RESET)"
# @$(CC) $(CFLAGS) $(OBJ) $(LIBFT) $(LDFLAGS) -o $@
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
	@echo "$(RED)╔══ Cleaning up ══╗$(RESET)"
	@make -C $(LIBFT_DIR) clean
	@rm -f $(OBJ)
	@echo "$(YELLOW)➜ Removed object files$(RESET)"
	@echo "$(GREEN)✔ Clean complete$(RESET)"
	@echo "$(RED)╚═════════════════╝$(RESET)"

fclean: clean
	@echo "$(RED)╔══ Deep cleaning ══╗$(RESET)"
	@make -C $(LIBFT_DIR) fclean
	@rm -f $(NAME)
	@echo "$(YELLOW)➜ Removed $(BOLD)$(NAME)$(RESET)"
	@echo "$(GREEN)✔ Full clean complete$(RESET)"
	@echo "$(RED)╚═══════════════════╝$(RESET)"

# $(RDLINE_OBJS):%.o: %.c $(INCLUDES) $(RDLINE)
# 	@cc $(CFLAGS) -I $(RDLINE)/include -c $< -o $@ 

# $(RDLINE) :
# 	@brew install readline

# run : 
# 	@./$(NAME)

# readline : $(RDLINE)


re: fclean all
