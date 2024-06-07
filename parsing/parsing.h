/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achakkaf <achakkaf@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/27 13:12:12 by achakkaf          #+#    #+#             */
/*   Updated: 2024/06/06 17:41:09 by achakkaf         ###   ########.fr       */
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
# define DOUBLE_Q 22
#define TAB 9
#define SPACE 32

// <Makefile>out cat|wc>test|grep -v "test">out<Make""'file'""""

typedef enum s_type {
	infile = 1,
	oufile = 2,
	append = 3,
	here_doc = 4,
} t_type;

typedef struct s_file{
	char *name; //name file ds
	t_type type;
	struct  s_file *next;
	
} t_file;

typedef struct s_cmd
{
	char	**args;
	char	*path;
	int		*status;
	t_file *files;
	struct s_cmd *next;
}	t_cmd;

typedef struct s_env
{
	char *key;
	char *value;
	struct s_env *next;
} t_env;

typedef struct s_parsing_info
{
	int start;
	int end;
	int cmd_i;
	int file;
	t_env *env;
} t_parsing_info;

/*-----------------------var_tooles----------------------*/
/// @brief Checks if the given name is valid
/// @return macros GOOD if valid else ERROR 
int check_name(char *name);

/// @brief Search for the variable name in the env and return it value
/// @return value or NULL if the variable name doesn't execte at env
char *get_var_value(t_env *env, char *var_name);

/// @brief Extract the variable name from a string
/// @return variable name
char *get_var_name(char *string, t_parsing_info *info);

/// @brief Extand all variables in a string if there are next each other
/// @return variables value or NULL if no variable execte at env
char *var_extand(char *string, t_parsing_info *info);

/// @brief what should you do when you find a dollar sign
/// @return string with extanded all the variable in the string
char *dollar_sign(char *string, t_parsing_info *info, char *var_value);

/*----------------------split_cmd----------------------*/

char **split_cmd(char *line);

/// @brief appand and element to end of an array
char **append_array(char **old_array, char *arg);

/*-----------------------parsing----------------------*/

char *filter(char *line, t_parsing_info *info);
t_cmd *parse_cmds(char **split_cmd, t_env *env);
int create_files(t_cmd *cmd, char **line, t_parsing_info *info, t_type type);
char *single_quote(char *line, t_parsing_info *info);
char *double_without(char *part, t_parsing_info *info, int flage);

#endif
