/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achakkaf <achakkaf@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/27 13:12:12 by achakkaf          #+#    #+#             */
/*   Updated: 2024/06/10 15:43:03 by achakkaf         ###   ########.fr       */
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


typedef struct s_file{
	char **name;
	t_type type;
	struct  s_file *next;
} t_file;

typedef struct s_cmd
{
	char	**args;
	char	*path;
	int		*status; // handle this
	t_file	*files;
	struct s_cmd *next;
}	t_cmd;

typedef struct s_env
{
	char *key;
	char *value;
	struct s_env *next;
} t_env;

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

/*-----------------------var_tooles----------------------*/
/// @brief Checks if the given name is valid
/// @return macros GOOD if valid else ERROR 
int check_name(char *name);

/// @brief Search for the variable name in the env and return it value
/// @return value or NULL if the variable name doesn't execte at env
char *get_var_value(t_env *env, char *var_name);

/// @brief Extract the variable name from a string
/// @return variable name
char *get_var_name(char *string, t_info *info);

/// @brief Extand all variables in a string if there are next each other
/// @return variables value or NULL if no variable execte at env
char *var_extand(char *string, t_info *info);

/// @brief what should you do when you find a dollar sign
/// @return string with extanded all the variable in the string
char *dollar_sign(char *string, t_info *info, char *var_value);

/*----------------------split_line----------------------*/

/// @brief this function will split a line to a tokens
/// @return an array of tokens
char **split_line(char *line);

/// @brief free an array
void free_array(char ***array);

/// @brief calculate size of an array
/// @return size of the array
int array_size(char **array);

/// @brief add arg to end of an array and free the old array
/// @return new array with arg as a last pramiter
char **append_array(char **old_array, char *arg);

/// @brief create a commands linked list with all info in command and its args, rediraction functions, status pointer ...
/// @param tokens An array of tokens 
/// @param status address of status variable
/// @return head of the command linked list
/// @note it return NULL if tokens is NULL or create_cmd function faild or faild to allocate
t_cmd *parse_cmds(char **tokens, t_env *env, int *status);



t_cmd *parsing(char *line, t_env *env, int *status);
int check_next(char *str, char *line);
int create_files(t_cmd *cmd, char **line, t_info *info, t_type type);
void free_cmd(t_cmd *cmd);
char *parsing_extend_var(char *string, t_env *env, int *status);
char **parsing_split(char *string);
char *filter(char *part);
int set_default(t_cmd **cmd, int *status);
void add_back_cmd(t_cmd *head, t_cmd *next_command);
char *quation_mark(char *string, t_info *info, char *var_value, int *status);
int quote_skip(char *str, int *index, char quote);
void alloc_appand(char *line, int start, int end, char ***words_symboles);

#endif
