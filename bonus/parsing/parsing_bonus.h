/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_bonus.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abounab <abounab@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/27 13:12:12 by achakkaf          #+#    #+#             */
/*   Updated: 2024/07/07 12:17:57 by abounab          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#ifndef PARSING_BONUS_H
#define PARSING_BONUS_H

#include "../types_bonus.h"
// #include "../env/env.h"

int     check_name(char *name);
char    *get_var_value(t_env *env, char *var_name);
char    *get_var_name(char *string, t_info *info);
char	*var_extand(char *string, t_info *info);
char	*dollar_sign(char *string, t_info *info, char *var_value);
char	**split_line(char *line);
void	free_array(char ***array);
int		array_size(char **array);
char	**append_array(char **old_array, char *arg);
t_cmd	*parse_cmds(char **tokens, t_env *env, int *status);
t_cmd	*parsing(char *line, t_env *env, int *status);
int		check_next(char *str, int *status);
int		create_files(t_cmd *cmd, char **line, t_info *info, t_type type);
void	free_cmd(t_cmd *cmd);
char	*parsing_extend_var(char *string, t_env *env, int *status, int *expend);
char	**parsing_split(char *string);
char	*ft_filter(char *part);
int		set_default(t_cmd **cmd, int *status);
void	add_back_cmd(t_cmd *head, t_cmd *next_command);
char	*quation_mark(char *string, t_info *info, char *var_value, int *status);
int		quote_skip(char *str, int *index, char quote);
void	alloc_appand(char *line, int start, int end, char ***words_symboles);


// wildcads
char *wildcard(char *pattern);
char *var_wildcard(char *line);
void print_array(char **array);

char *join_array(char **array);
int check_paro(char **array);
int check_f_l(char **array);
char **remove_f_l(char **array);
void split_and_or(t_bonus *bonus);


char **sub_split(char **array, int start, int end);
int	bonus_addback(t_bonus **lst, t_bonus *newnode);
int skip_p(char **array, int index);
int skip_and_or(char **array, int index);
t_bonus *ft_bonussplit(t_bonus *bonus);
int skip_s(char **array, int index, char *s1);

#endif

