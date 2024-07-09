/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_split.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achakkaf <achakkaf@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/09 12:57:09 by achakkaf          #+#    #+#             */
/*   Updated: 2024/07/09 12:57:46 by achakkaf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"



int blank_quote(char *line, int start, int *end, char ***split_string)
{
	while (line[*end] && line[*end] != SPACE && line[*end] != TAB)
	{
		if (line[*end] == '\'')
		{
			if (quote_skip(line, &*end, '\'') == ERROR)
			{
				free_array(split_string);
				return (ERROR);
			}
		}
		else if (line[*end] == '"')
		{
			if (quote_skip(line, &*end, '"') == ERROR)
			{
				free_array(split_string);
				return (ERROR);
			}
		}
		(*end)++;
	}
	alloc_appand(line, start, *end, split_string);
	return (GOOD);
}

char **parsing_split(char *string)
{
	char **split_string;
	int start;
	int end;

	end = 0;
	split_string = NULL;
	while (string && string[end])
	{
		while (string[end] && (string[end] == SPACE || string[end] == TAB))
			end++;
		start = end;
		if (string[end] || string[end] == '"' || string[end] == '\'')
		{
			if (blank_quote(string, start, &end, &split_string))
				return (NULL);
		}
	}
	return (split_string);
}
