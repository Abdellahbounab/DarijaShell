/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_cmd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achakkaf <achakkaf@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/12 09:41:34 by Achakkaf          #+#    #+#             */
/*   Updated: 2024/05/30 18:48:52 by achakkaf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

#define TAB 9
#define SPACE 32

static int skip_q(char *s, int *i)
{
	if (s[*i] == '\'')
	{
		(*i)++;
		while (s[*i] != '\'' && s[*i])
			(*i)++;
	}
	else if (s[*i] == '"')
	{
		(*i)++;
		while (s[*i] != '"' && s[*i])
			(*i)++;
	}
	if (s[*i] == '\0')
		return (write(STDERR_FILENO, "close the Quotation\n", 21), ERROR);
	return (GOOD);
}

static int new_cwords(char *s)
{
	int i;
	int count;
	int inword;

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
			if (skip_q(s, &i) != GOOD)
				return (ERROR);
			i++;
		}
		inword = 1;
	}
	return (count);
}

static char *new_substr(char *str, int start, int end)
{
	char *sstr;
	int i;

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

static void split_cmd2(char *cmd, int *start, int *end)
{
	while ((cmd[*end] == SPACE || cmd[*end] == TAB) && cmd[*end])
		(*end)++;
	*start = *end;
	while (cmd[*end] != SPACE && cmd[*end] != TAB && cmd[*end])
	{
		if (cmd[*end] == '\'')
		{
			(*end)++;
			while (cmd[*end] != '\'' && cmd[*end])
				(*end)++;
		}
		else if (cmd[*end] == '"')
		{
			(*end)++;
			while (cmd[*end] != '"' && cmd[*end])
				(*end)++;
		}
		(*end)++;
	}
}

char **split_cmd(char *command)
{
	char **cmd;
	int end;
	int start;
	int i;
	int n_words;

	i = 0;
	end = 0;
	n_words = new_cwords(command);
	if (n_words == ERROR || n_words == 0)
		return (NULL);
	cmd = malloc((n_words + 2) * sizeof(char *));
	while (cmd && command[end])
	{
		split_cmd2(command, &start, &end);
		if (start != end)
			cmd[i] = new_substr(command, start, end);
		else
			break;
		i++;
	}
	if (cmd)
	{
		cmd[i++] = "\n";
		cmd[i] = NULL;
	}
	return (cmd);
}
