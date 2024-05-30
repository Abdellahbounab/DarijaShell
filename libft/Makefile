# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: Achakkaf <zizcarschak1@gmail.com>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/12/10 17:20:23 by Achakkaf          #+#    #+#              #
#    Updated: 2023/12/26 09:15:24 by Achakkaf         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = cc
CFLAGS  = -Wall -Wextra -Werror
NAME = libft.a 

CFILES =	ft_atoi.c \
			ft_bzero.c \
			ft_calloc.c \
			ft_isalnum.c \
			ft_isalpha.c \
			ft_isascii.c \
			ft_isdigit.c \
			ft_isprint.c \
			ft_memchr.c \
			ft_memcmp.c \
			ft_memcpy.c \
			ft_memmove.c \
			ft_memset.c \
			ft_strchr.c \
			ft_strrchr.c \
			ft_strdup.c \
			ft_strjoin.c \
			ft_strlcat.c \
			ft_strlcpy.c \
			ft_strlen.c \
			ft_strncmp.c \
			ft_strnstr.c \
			ft_substr.c \
			ft_tolower.c \
			ft_toupper.c \
			ft_strtrim.c \
			ft_split.c \
			ft_itoa.c \
			ft_strmapi.c \
			ft_striteri.c \
			ft_putchar_fd.c \
			ft_putstr_fd.c \
			ft_putendl_fd.c \
			ft_putnbr_fd.c 

BFILES =	ft_lstnew_bonus.c \
			ft_lstadd_front_bonus.c \
			ft_lstsize_bonus.c \
			ft_lstlast_bonus.c \
			ft_lstadd_back_bonus.c \
			ft_lstdelone_bonus.c \
			ft_lstclear_bonus.c \
			ft_lstiter_bonus.c \
			ft_lstmap_bonus.c \
			

OFILES = $(CFILES:.c=.o)
OBFILES = $(BFILES:.c=.o)

all : $(NAME)

$(NAME): $(OFILES)
	ar rcs $(NAME) $(OFILES)

%.o:%.c libft.h
	$(CC) $(CFLAGS) -c $< -o $@

bonus : $(OBFILES)
	ar rcs $(NAME) $(OBFILES)

clean : 
	rm -f $(OFILES) $(OBFILES)

fclean: clean
	rm -f $(NAME)

re : fclean all

.PHONY: all clean fclean re bonus