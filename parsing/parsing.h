/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achakkaf <achakkaf@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/27 13:12:12 by achakkaf          #+#    #+#             */
/*   Updated: 2024/07/09 15:39:37 by achakkaf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#ifndef PARSING_H
#define PARSING_H

#include "../types.h"
#include "../env/env.h"

int     check_name(char *name);
char    *get_var_value(t_env *env, char *var_name);
char    *get_var_name(char *string, t_info *info);
char	*var_extand(char *string, t_info *info);
char	*dollar_sign(char *string, t_info *info, char *var_value, int *is_expend);
char	**split_line(char *line);
void	free_array(char ***array);
int		array_size(char **array);
char	**append_array(char **old_array, char *arg);
t_cmd	*parse_cmds(char **tokens, t_env *env);
t_cmd	*parsing(char *line, t_env *env);
int		check_next(char *str);
int		create_files(t_cmd *cmd, char **line, t_info *info, t_type type);
void	free_cmd(t_cmd *cmd);
char    *parsing_extend_var(char *string, t_env *env, int *expend);
char	**parsing_split(char *string);
char	*ft_filter(char *part);
// void	add_back_cmd(t_cmd *head, t_cmd *next_command);
char	*quation_mark(char *string, t_info *info, char *var_value);
int		quote_skip(char *str, int *index, char quote);
void	alloc_appand(char *line, int start, int end, char ***words_symboles);
char    *wildcard(char *pattern, t_env *env);
char    *var_wildcard(char *line , t_env *env);
char    **get_files(t_env *env);
void swap_str(char **stra, char **strb);
void sort_by_name(char **array);
int take_files(char **tokens, t_cmd *cmd, t_info *info);
bool match(char *filename, const char *pattern);
char *star_magic(char *token, int is_expend, t_env *env);
int create_files(t_cmd *cmd, char **tokens, t_info *info, t_type type);
void add_back_file(t_cmd *cmd, t_file *file);
int pipe_checker(t_cmd *cmd, char **tokens, t_info *info);
char *star_magic(char *token, int is_expend, t_env *env);
void add_back_cmd(t_cmd *head, t_cmd *next_command);
char **parsing_split(char *string);

#endif
