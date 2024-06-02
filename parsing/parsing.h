/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achakkaf <achakkaf@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/27 13:12:12 by achakkaf          #+#    #+#             */
/*   Updated: 2024/06/02 16:06:51 by achakkaf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
#define PARSING_H

#include <stdlib.h>
#include <stdio.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <unistd.h>
#include "../libft/libft.h"
#include <fcntl.h>

# define ERROR -1
# define GOOD 0

#define TAB 9
#define SPACE 32

// <Makefile>out cat|wc>test|grep -v "test">out<Make""'file'""""

typedef enum s_type {
	here_doc = 1,
	infile = 2,
	append = 3,
	oufile = 4,
} t_type;
typedef struct s_file{
	char *name; //name file ds
	t_type type;
} t_file;

typedef struct s_cmd
{
	char	**args;
	char	*path;
	int		*status;
	t_file **files;
	struct s_cmd *next;
}	t_cmd;

// typedef struct s_var_info
// {
// 	char *name;
// 	int len;
// } t_var_info;

// //variables are type string
typedef struct s_env
{
	char *key;
	char *value;
	struct s_env *next;
} t_env;

char **split_cmd(char *line);

/// @brief appand and element to end of an array
char **append_array(char **old_array, char *arg);

int check_name(char *name);
char *var_name(char *token);
// char *single_q_filter(char *token, int *start);
char *filter(char *line, t_env *env);
#endif