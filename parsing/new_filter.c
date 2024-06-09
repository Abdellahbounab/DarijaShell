/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   new_filter.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achakkaf <achakkaf@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/06 17:05:59 by achakkaf          #+#    #+#             */
/*   Updated: 2024/06/09 11:49:07 by achakkaf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

char *single_quote(char *part, int *end)
{
	int start;

	(*end)++;
	start = *end;
	while (part[*end] && part[*end] != '\'')
		(*end)++;
	return (ft_substr(part, start, (*end)++ - start));
}

char *double_without(char *part, int *end, int flage)
{
	char *var_value;
	char *string;
	char *tmp;
	int start;

	string = NULL;
	var_value = NULL;
	start = *end;
	while (part[*end])
	{
		if (flage == DOUBLE_Q && part[*end] == '"')
			break;
		else if (flage != DOUBLE_Q && (part[*end] == '"' || part[*end] == '\''))
			break;
		else
			(*end)++;
	}
	tmp = ft_substr(part, start, *end - start);
	string = ft_strjoin(var_value, tmp);
	free(tmp);
	free(var_value);
	return (string);
}

char *filter(char *part)
{
	char *tmp;
	char *tmp_free;
	char *token;
	int end;

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
		tmp_free = token;
		token = ft_strjoin(token, tmp);
		free(tmp_free);
		free(tmp);
		tmp = NULL;
	}
	return (token);
}
