/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_var.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achakkaf <achakkaf@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/16 10:46:42 by achakkaf          #+#    #+#             */
/*   Updated: 2024/07/16 10:58:42 by achakkaf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

static char	*extend_var_logic(char *string, t_info *info, \
	int *is_expend)
{
	char	*tmp;

	tmp = NULL;
	while (string[info->end])
	{
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

char	*heredoc_var(char *string, t_env *env, int *is_expend)
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
	free(tmp);
	free(info);
	return (new_string);
}
