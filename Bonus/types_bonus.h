
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   types_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achakkaf <achakkaf@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/11 11:30:27 by achakkaf          #+#    #+#             */
/*   Updated: 2024/06/26 14:06:11 by achakkaf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TYPES_H
#define TYPES_H

#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <readline/readline.h>
#include <readline/history.h>
#include "../libft/libft.h"
#include <dirent.h>
#include <stdbool.h>

# define ERROR -1
# define GOOD 0

# define SINGLE_Q 39
# define DOUBLE_Q 34
# define WITHOUT 32

#define TAB 9
#define SPACE 32

typedef enum s_type {
	INFILE = 1,
	OUFILE = 2,
	APPEND = 3,
	HERE_DOC = 4,
} t_type;

typedef struct s_env
{
	char *key;
	char *value;
	struct s_env *next;
} t_env;

typedef struct s_file{
	char **name;
	t_type type;
	struct  s_file *next;
} t_file;

typedef struct s_cmd
{
	char	**args;
	char	*path;
	int		*status;
	t_file	*files;
	struct s_cmd *next;
}	t_cmd;

typedef struct s_info
{
	int start;
	int end;
	int cmd_i;
	int file;
	int dollar;
	int var_from;
	t_env *env;
	t_cmd *cmd;
} t_info;


#endif