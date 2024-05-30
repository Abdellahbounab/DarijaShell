/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_cmd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achakkaf <achakkaf@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/12 09:41:34 by Achakkaf          #+#    #+#             */
/*   Updated: 2024/05/28 11:37:37 by achakkaf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

# define TAB 9
# define SPACE 32

void	skip_q(char *s, int *i)
{
	if (s[*i] == '\'' || s[*i] == '"')
	{
		(*i)++;
		while ((s[*i] != '\'' && s[*i] != '"') && s[*i])
			(*i)++;
	}
}

int	new_cwords(char *s)
{
	int	i;
	int	count;
	int	inword;

	i = 0;
	inword = 1;
	count = 0;
	while (s && s[i])
	{
		while ((s[i] == SPACE || s[i] == TAB) && s[i])
			i++;
		while (s[i] != SPACE && s[i] != TAB && s[i])
		{
			if (inword)
			{
				count++;
				inword = 0;
			}
			skip_q(s, &i);
			i++;
		}
		inword = 1;
	}
	return (count);
}

char	*new_substr(char *str, int start, int end)
{
	char	*sstr;
	int		i;

	i = 0;
	if (str == NULL)
		return (NULL);
	sstr = malloc((end - start + 1) * sizeof(char));
	if (sstr == NULL)
		return (NULL);
	while (start < end && str[start])
	{
		sstr[i] = str[start];
		start++;
		i++;
	}
	sstr[i] = '\0';
	return (sstr);
}

void	split_cmd2(char *cmd, int *start, int *end, int *in)
{
	while ((cmd[*end] == SPACE || cmd[*end] == TAB) && cmd[*end])
		(*end)++;
	*start = *end;
	while (cmd[*end] != SPACE && cmd[*end] != TAB && cmd[*end])
	{
		if (cmd[*end] == '\'' || cmd[*end] == '"')
		{
			(*end)++;
			*start = *end;
			while ((cmd[*end] != '\'' && cmd[*end] != '"') && cmd[*end])
				(*end)++;
			*in = 1;
		}
		(*end)++;
	}
}

char	**split_cmd(char *command)
{
	char	**cmd;
	int		end;
	int		start;
	int		i;
	int		in;

	in = 0;
	i = 0;
	end = 0;
	cmd = malloc((new_cwords(command) + 1) * sizeof(char *));
	while (cmd && command && command[end])
	{
		split_cmd2(command, &start, &end, &in);
		if (start != end)
		{
			cmd[i] = new_substr(command, start, end - in);
			in = 0;
		}
		else
			break ;
		i++;
	}
	if (cmd)
		cmd[i] = NULL;
	return (cmd);
}
