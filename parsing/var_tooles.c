/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   var_tooles.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achakkaf <achakkaf@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/01 17:50:44 by achakkaf          #+#    #+#             */
/*   Updated: 2024/06/09 14:27:50 by achakkaf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

int check_name(char *name)
{
	int i;

	i = 0;
	if (name && ft_isdigit(name[i]) == GOOD)
		return (ERROR);
	while (name && name[i])
	{
		if (ft_isalpha(name[i]) == ERROR && ft_isdigit(name[i]) == ERROR && name[i] != '_')
			return (ERROR);
		i++;
	}
	return (GOOD);
}

char *get_var_value(t_env *env, char *var_name)
{
	while (env)
	{
		if (ft_strcmp(env->key, var_name) == GOOD)
			return (env->value);
		env = env->next;
	}
	return (NULL);
}

char *get_var_name(char *string, t_parsing_info *info)
{
	while (string[info->end] && (ft_isalpha(string[info->end]) == GOOD || ft_isdigit(string[info->end]) == GOOD || string[info->end] == '_'))
		info->end++;
	return (ft_substr(string, info->start, info->end - info->start));
}

char *var_extand(char *part, t_parsing_info *info)
{
	char *string;
	char *var_name;
	char *tmp;
	char *var_value;
	t_env *tmp_env;

	string = NULL;
	while (part[info->end] == '$')
	{
		info->end++;
		info->start = info->end;
		var_name = get_var_name(part, info);
		// printf("var_name:%s\n", var_name);
		var_value = get_var_value(info->env, var_name);
		// printf("var_value:%s\n", var_value);
		free(var_name);
		var_name = NULL;
		tmp = string;
		string = ft_strjoin(string, var_value);
		free(tmp);
	}
	info->start = info->end;
	return (string);
}

char *dollar_sign(char *string, t_parsing_info *info, char *var_value)
{
	char *before_dollar;
	char *tmp;

	before_dollar = ft_substr(string, info->start, info->end - info->start);
	// printf("before_dollar1:%s\n", before_dollar);
	tmp = before_dollar;
	before_dollar = ft_strjoin(var_value, before_dollar);
	// printf("before_dollar2:%s\n", before_dollar);
	free(tmp);
	free(var_value);
	var_value = var_extand(string, info);
	// printf("var_value1:%s\n", var_value);
	tmp = var_value;
	var_value = ft_strjoin(before_dollar, var_value);
	// printf("var_value2:%s\n", var_value);
	free(tmp);
	free(before_dollar);
	return (var_value);
}

char *quation_mark(char *string, t_parsing_info *info, char *var_value, int *status)
{
	char *before_dollar;
	char *tmp;

	before_dollar = ft_substr(string, info->start, info->end - info->start);
	// printf("before_dollar1:%s\n", before_dollar);
	tmp = before_dollar;
	before_dollar = ft_strjoin(var_value, before_dollar);
	// printf("before_dollar2:%s\n", before_dollar);
	free(tmp);
	free(var_value);
	var_value = ft_itoa(*status);
	// printf("var_value1:%s\n", var_value);
	tmp = var_value;
	var_value = ft_strjoin(before_dollar, var_value);
	// printf("var_value2:%s\n", var_value);
	free(tmp);
	free(before_dollar);
	return (var_value);
}