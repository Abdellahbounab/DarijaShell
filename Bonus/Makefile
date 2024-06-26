
NAME := minishell_bonus
CC := cc
CFLAGS := -Wall -Wextra -Werror
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
       parsing_bonus/cmd_bonus.c \
       parsing_bonus/free_bonus.c \
       parsing_bonus/new_filter_bonus.c \
       parsing_bonus/new_parsing_bonus.c \
       parsing_bonus/parsing_tooles_bonus.c \
       parsing_bonus/split_line_bonus.c \
       parsing_bonus/var_tooles_bonus.c \
       parsing_bonus/wildcards_bonus.c

INCLUDES := parsing_bonus/parsing_bonus.h \
            types_bonus.h

OBJ := $(SRC:.c=.o)

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

$(NAME): $(OBJ) $(LIBFT)
	@echo "$(ORG)╔══ Linking object files ══╗$(RESET)"
	@echo "$(CYAN)➜ Creating executable: $(BOLD)$(NAME)$(RESET)"
	@$(CC) $(CFLAGS) $(OBJ) $(LIBFT) $(LDFLAGS) -o $@
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

re: fclean all
