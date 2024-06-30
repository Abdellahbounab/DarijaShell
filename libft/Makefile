# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: achakkaf <achakkaf@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/06/25 11:58:33 by achakkaf          #+#    #+#              #
#    Updated: 2024/06/26 10:07:55 by achakkaf         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

BOLD := \033[1m
CYAN := \033[36m
GREEN := \033[32m
YELLOW := \033[33m
RED := \033[31m
RESET := \033[0m

CC := cc
CFLAGS := -Wall -Wextra -Werror

NAME := libft.a

CFILES := ft_atoi.c ft_bzero.c ft_calloc.c ft_isalnum.c ft_isalpha.c \
          ft_isascii.c ft_isdigit.c ft_isprint.c ft_memchr.c ft_memcmp.c \
          ft_memcpy.c ft_memmove.c ft_memset.c ft_strchr.c ft_strrchr.c \
          ft_strdup.c ft_strjoin.c ft_strlcat.c ft_strlcpy.c ft_strlen.c \
          ft_strncmp.c ft_strnstr.c ft_substr.c ft_tolower.c ft_toupper.c \
          ft_strtrim.c ft_split.c ft_itoa.c ft_strmapi.c ft_striteri.c \
          ft_putchar_fd.c ft_putstr_fd.c ft_putendl_fd.c ft_putnbr_fd.c

BFILES := ft_lstnew_bonus.c ft_lstadd_front_bonus.c ft_lstsize_bonus.c \
          ft_lstlast_bonus.c ft_lstadd_back_bonus.c ft_lstdelone_bonus.c \
          ft_lstclear_bonus.c ft_lstiter_bonus.c ft_lstmap_bonus.c

OFILES := $(CFILES:.c=.o)
OBFILES := $(BFILES:.c=.o)

define LIBFT_LOGO
$(BOLD)$(CYAN)
    __    ________  ________
   / /   /  _/ __ )/ ____/ /_
  / /    / // __  / /_  / __/
 / /____/ // /_/ / __/ / /_
/_____/___/_____/_/   \__/
$(RESET)
endef
export LIBFT_LOGO

all: print_logo $(NAME)

print_logo:
	@echo "$$LIBFT_LOGO"
	@echo "$(YELLOW)Building libft...$(RESET)"

$(NAME): $(OFILES)
	@ar rcs $(NAME) $(OFILES)
	@echo "$(GREEN)✔ $(BOLD)$(NAME)$(RESET)$(GREEN) created successfully$(RESET)"

%.o: %.c libft.h
	@echo "$(YELLOW)➜ Compiling: $(BOLD)$<$(RESET)"
	@$(CC) $(CFLAGS) -c $< -o $@

bonus: $(NAME) $(OBFILES)
	@echo "$(CYAN)╔══ Adding bonus functions ══╗$(RESET)"
	@ar rcs $(NAME) $(OBFILES)
	@echo "$(GREEN)✔ Bonus functions added to $(BOLD)$(NAME)$(RESET)"
	@echo "$(CYAN)╚═════════════════════════════╝$(RESET)"

clean:
	@rm -f $(OFILES) $(OBFILES)

fclean: clean
	@rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re bonus print_logo
