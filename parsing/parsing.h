/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achakkaf <achakkaf@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/27 13:12:12 by achakkaf          #+#    #+#             */
/*   Updated: 2024/06/24 16:57:16 by achakkaf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
#define PARSING_H

#include "../types.h"

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

/// @brief this where all the algorith of parsing is
/// @param line reading line from readline function
/// @param env envirment variable
/// @param status the address of status variable
/// @return a head of all command in the linked list
t_cmd	*parsing(char *line, t_env *env, int *status);

int		check_next(char *str, int *status);
int		create_files(t_cmd *cmd, char **line, t_info *info, t_type type);
void	free_cmd(t_cmd *cmd);
char	*parsing_extend_var(char *string, t_env *env, int *status);
char	**parsing_split(char *string);
char	*filter(char *part);
int		set_default(t_cmd **cmd, int *status);
void	add_back_cmd(t_cmd *head, t_cmd *next_command);
char	*quation_mark(char *string, t_info *info, char *var_value, int *status);
int		quote_skip(char *str, int *index, char quote);
void	alloc_appand(char *line, int start, int end, char ***words_symboles);

#endif
