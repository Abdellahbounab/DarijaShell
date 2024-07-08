/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achakkaf <achakkaf@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/08 11:15:13 by achakkaf          #+#    #+#             */
/*   Updated: 2024/07/08 13:03:45 by achakkaf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing_bonus.h"

/*						Algorithm of a new parsing
	ar= "s -l"	;	"l"$ar't'a	-> "l"s -l't'a	-> ["l"s -l't'a]	->	[ls -lta]
	ar=			;	"l"$ar't'a	-> "l"'t'a		-> ["l"'t'a]		->	[lta]
	ar= hello	;	$ar			-> hello		-> [hello]			->	[hello]
*/
static void double_quote(char *string, t_info *info, char **tmp, int *status)
{
	info->end++;
	while (string[info->end] && string[info->end] != '"')
	{
		if (string[info->end] == '$')
		{
			if (string[info->end + 1] == '?')
			{
				*tmp = quation_mark(string, info, *tmp, status);
				info->end += 2;
			}
			else
				*tmp = dollar_sign(string, info, *tmp);
			info->start = info->end;
		}
		else
			info->end++;
	}
}
static char *extend_var_logic(char *string, t_info *info, int *status)
{
	char *tmp;

	tmp = NULL;
	while (string[info->end])
	{
		if (string[info->end] == '\'')
			quote_skip(string, &info->end, '\'');
		if (string[info->end] == '"')
			double_quote(string, info, &tmp, status);
		if (string[info->end] == '$')
		{
			if (string[info->end + 1] == '?')
			{
				tmp = quation_mark(string, info, tmp, status);
				*status = 0;
				info->end += 2;
			}
			else
				tmp = dollar_sign(string, info, tmp);
			info->start = info->end;
		}
		else
			info->end++;
	}
	return (tmp);
}

char *parsing_extend_var(char *string, t_env *env, int *status, int *expend)
{
	t_info *info;
	char *tmp;
	char *new_string;
	char *tmp_free;

	if (string == NULL)
		return (NULL);
	info = malloc(sizeof(t_info));
	if (info == NULL)
		return (NULL);
	info->end = 0;
	info->start = 0;
	info->env = env;
	new_string = NULL;
	tmp = extend_var_logic(string, info, status);
	if (tmp && expend)
		*expend = 1;
	new_string = ft_substr(string, info->start, info->end - info->start);
	tmp_free = new_string;
	new_string = ft_strjoin(tmp, new_string);
	free(tmp_free);
	free(tmp);
	free(info);
	return (new_string);
}

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

t_cmd *parsing(char **tokens, t_env *env, int *status)
{
	// char **tokens;
	t_cmd *cmds_head;

	// tokens = split_line(line);
	// free(line);
	// line = NULL;
	cmds_head = parse_cmds(tokens, env, status);
	// free_array(&tokens);
	return (cmds_head);
}
