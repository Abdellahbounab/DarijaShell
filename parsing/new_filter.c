/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   new_filter.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achakkaf <achakkaf@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/06 17:05:59 by achakkaf          #+#    #+#             */
/*   Updated: 2024/07/16 10:33:44 by achakkaf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

char	*quation_mark(char *string, t_info *info, char *var_value)
{
	char	*before_dollar;
	char	*tmp;

	before_dollar = ft_substr(string, info->start, info->end - info->start);
	tmp = before_dollar;
	before_dollar = ft_strjoin(var_value, before_dollar);
	free(tmp);
	free(var_value);
	var_value = ft_itoa(g_status);
	tmp = var_value;
	var_value = ft_strjoin(before_dollar, var_value);
	free(tmp);
	free(before_dollar);
	return (var_value);
}

char	*single_quote(char *part, int *end)
{
	int	start;

	(*end)++;
	start = *end;
	while (part[*end] && part[*end] != '\'')
		(*end)++;
	return (ft_substr(part, start, (*end)++ - start));
}

char	*double_without(char *part, int *end, int flage)
{
	char	*var_value;
	char	*string;
	char	*tmp;
	int		start;

	string = NULL;
	var_value = NULL;
	start = *end;
	while (part[*end])
	{
		if (flage == DOUBLE_Q && part[*end] == '"')
			break ;
		else if (flage != DOUBLE_Q && (part[*end] == '"' || part[*end] == '\''))
			break ;
		else
			(*end)++;
	}
	tmp = ft_substr(part, start, *end - start);
	string = ft_strjoin(var_value, tmp);
	free(tmp);
	free(var_value);
	return (string);
}

char	*join_free(char **old_str, char **add_str)
{
	char	*tmp;
	char	*token;

	tmp = *old_str;
	token = ft_strjoin(*old_str, *add_str);
	free(tmp);
	free(*add_str);
	*add_str = NULL;
	return (token);
}

char	*ft_filter(char *part)
{
	char	*tmp;
	char	*token;
	int		end;

	end = 0;
	token = NULL;
	while (part && part[end])
	{
		if (part[end] == '\'')
			tmp = single_quote(part, &end);
		else if (part[end] == '"')
		{
			end++;
			tmp = double_without(part, &end, DOUBLE_Q);
			end++;
		}
		else
			tmp = double_without(part, &end, -22);
		token = join_free(&token, &tmp);
	}
	return (token);
}
