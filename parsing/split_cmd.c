/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_cmd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achakkaf <achakkaf@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/01 12:31:21 by achakkaf          #+#    #+#             */
/*   Updated: 2024/06/02 11:11:33 by achakkaf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

void free_array(char ***array)
{
	int size;

	size = 0;
	while (array && *array && (*array)[size])
		free((*array)[size++]);
	free((*array));
}

char **append_array(char **old_array, char *arg)
{
	int size;
	char **new_array;

	if (arg == NULL)
		return (old_array);
	size = 0;
	while (old_array && old_array[size])
		size++;
	new_array = malloc(sizeof(char *) * (size + 2));
	if (new_array == NULL)
		return (NULL);
	if (old_array == NULL)
	{
		new_array[0] = ft_strdup(arg);
		new_array[1] = NULL;
		return (new_array);
	}
	size = 0;
	while (old_array[size])
	{
		new_array[size] = ft_strdup(old_array[size]);
		free(old_array[size]);
		size++;
	}
	free(old_array);
	new_array[size++] = ft_strdup(arg);
	new_array[size] = NULL;
	return (new_array);
}

int quote_skip(char *str, int *index, char quote)
{
	(*index)++;
	while (str[*index] && str[*index] != quote)
		(*index)++;
	if (str[*index] != quote)
	{
		write(STDERR_FILENO, "close the quote\n", 17);
		return (ERROR);
	}
	return (GOOD);
}

void alloc_appand(char *line, int start, int end, char ***words_symboles)
{
	char *tmp;

	tmp = ft_substr(line, start, end - start);
	*words_symboles = append_array(*words_symboles, tmp);
	free(tmp);
}

int blank_quote(char *line, int start, int *end, char ***words_symboles)
{
	while (line[*end] && line[*end] != SPACE && line[*end] != TAB)
	{
		if (line[*end] == '\'')
		{
			if (quote_skip(line, &*end, '\'') == ERROR)
			{
				free_array(words_symboles);
				return (ERROR);
			}
		}
		else if (line[*end] == '"')
		{
			if (quote_skip(line, &*end, '"') == ERROR)
			{
				free_array(words_symboles);
				return (ERROR);
			}
		}
		else if (line[*end] == '>' || line[*end] == '<' || line[*end] == '|')
			break;
		(*end)++;
	}
	alloc_appand(line, start, *end, words_symboles);
	return (GOOD);
}

// cat -e "Makefile" 						-> 			[cat, -e, "Makefile"]
// < hello cat -e "Makefile" 				-> 			[< , hello, cat, -e , "Makefile"]
// helo>makefile<howled cat|wc >"out"'' 	-> 			[helo, >, makefile, <, howled, cat, |, wc, "out",'']
// hello>>out<<ok cat 						-> 			[hello, >>, out, <<, ok, cat]
char **split_cmd(char *line)
{
	char **words_symboles;
	int start;
	int end;

	end = 0;
	words_symboles = NULL;
	while (line && line[end])
	{
		while (line[end] && (line[end] == SPACE || line[end] == TAB))
			end++;
		start = end;
		if (line[end] && ((line[end] == '<' && line[end + 1] == '<') || (line[end] == '>' && line[end + 1] == '>')))
		{
			end = end + 2;
			alloc_appand(line, start, end, &words_symboles);
		}
		else if (line[end] == '<' || line[end] == '>' || line[end] == '|')
			alloc_appand(line, start, ++end, &words_symboles);
		else if (line[end] || line[end] == '"' || line[end] == '\'')
		{
			if (blank_quote(line, start, &end, &words_symboles))
				return (NULL);
		}
	}
	return (words_symboles);
}

// <Makefile>out cat|wc>test|grep  -v  "test">out<Make""'file'""""<<out?>>sdf wohot
