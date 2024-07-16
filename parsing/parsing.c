/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achakkaf <achakkaf@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/08 11:15:13 by achakkaf          #+#    #+#             */
/*   Updated: 2024/07/16 10:50:48 by achakkaf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

/*						Algorithm of a new parsing
	ar= "s -l"	;	"l"$ar't'a	-> "l"s -l't'a	-> ["l"s -l't'a]	->	[ls -lta]
	ar=			;	"l"$ar't'a	-> "l"'t'a		-> ["l"'t'a]		->	[lta]
	ar= hello	;	$ar			-> hello		-> [hello]			->	[hello]
	ar= "a v"	;	 < "$ar"	-> "a v"		-> ["a v", NULL]	->	[a v, NULL]
*/
static void	double_quote(char *string, t_info *info, char **tmp, int *is_expend)
{
	info->end++;
	while (string[info->end] && string[info->end] != '"')
	{
		if (string[info->end] == '$')
		{
			if (string[info->end + 1] == '?')
			{
				*tmp = quation_mark(string, info, *tmp);
				info->end += 2;
			}
			else
				*tmp = dollar_sign(string, info, *tmp, is_expend);
			info->start = info->end;
		}
		else
			info->end++;
	}
}

static void	single_quote(char *str, int *index)
{
	(*index)++;
	while (str[*index] && str[*index] != '\'')
		(*index)++;
}

static char	*extend_var_logic(char *string, t_info *info, \
	int *is_expend)
{
	char	*tmp;

	tmp = NULL;
	while (string[info->end])
	{
		if (string[info->end] == '\'')
			single_quote(string, &info->end);
		if (string[info->end] == '"')
			double_quote(string, info, &tmp, is_expend);
		if (string[info->end] == '$')
		{
			if (string[info->end + 1] == '?')
			{
				tmp = quation_mark(string, info, tmp);
				info->end += 2;
			}
			else
				tmp = dollar_sign(string, info, tmp, is_expend);
			info->start = info->end;
		}
		else
			info->end++;
	}
	return (tmp);
}

char	*parsing_extend_var(char *string, t_env *env, int *is_expend)
{
	t_info	*info;
	char	*tmp;
	char	*new_string;
	char	*tmp_free;

	if (string == NULL)
		return (NULL);
	info = ft_calloc(1, sizeof(t_info));
	if (info == NULL)
		return (NULL);
	info->env = env;
	tmp = extend_var_logic(string, info, is_expend);
	new_string = ft_substr(string, info->start, info->end - info->start);
	tmp_free = new_string;
	new_string = ft_strjoin(tmp, new_string);
	free(tmp_free);
	if (tmp && new_string && ft_strcmp(tmp, new_string))
	{
		tmp_free = new_string;
		new_string = ft_filter(new_string);
		free(tmp_free);
	}
	free(tmp);
	free(info);
	return (new_string);
}

t_cmd	*parsing(char *line, t_env *env)
{
	char	**tokens;
	t_cmd	*cmds_head;

	tokens = split_line(line);
	free(line);
	line = NULL;
	cmds_head = parse_cmds(tokens, env);
	free_array(&tokens);
	return (cmds_head);
}
