/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achakkaf <achakkaf@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/27 13:12:12 by achakkaf          #+#    #+#             */
/*   Updated: 2024/06/09 11:23:41 by achakkaf         ###   ########.fr       */
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

# define SINGLE_Q 39
# define DOUBLE_Q 34
# define WITHOUT 32

#define TAB 9
#define SPACE 32

// <Makefile>out cat|wc>test|grep -v "test">out<Make""'file'""""
// <Makefile>out<<$arg cat|wc>test|grep -v "test">out<Make""'file'""""
// $arg -> ls -la

typedef enum s_type {
	infile = 1,
	oufile = 2,
	append = 3,
	here_doc = 4,
} t_type;


// only redirect case :
// 		in case of <'$ar' ->return $ar and variable = 0; -> iwould undertand it as a file name and not to be extended
// 		in case of <$ar$ar1 -> return $ar and variable = 1; -> iwoudl understand it as to be extended
// 		in case of <"$ar" -> return extended variable in a file name


// in other cases than redirection : 
// << $ar -> return $ar as a delimiter and not extend it
// $ar -> return extended variable using split
// '$ar' -> return $ar as arg
// "$ar" -> return its value in a single arg

// < "helo wolr" cat < ls"$Ar" ar="ls -la"


typedef struct s_filenam{
	char *name; //splitted by $
	int	variable; //0 or 1
	struct s_file_name *next;
}t_filename;
typedef struct s_file{
	char *name;
	// t_filename *names;
	t_type type;
	int	text_type; //1 for extend else 0
	int	*pos;
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
	int dollar;
	int var_from;
	t_env *env;
	t_cmd *cmd;
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

void free_array(char ***array);
char *parsing_extend_var(char *string, t_env *env);
char **parsing_split(char *string);

#endif
