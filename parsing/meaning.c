/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   meaning.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achakkaf <achakkaf@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/02 11:21:18 by achakkaf          #+#    #+#             */
/*   Updated: 2024/06/02 12:10:45 by achakkaf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

// [< , Makefile]                                           ->      filenames[Makefile]
// [<, Makefile, >, output, cat, -e, >, ou ] 				->		filesnames:[Makefile, output, ou], input: Makefile, ouput: ou
// [<, 'Makefile', >, "out"put, cat, -e, >, ou ]			->		filesnames:[Makefile, output, ou], input: Makefile, ouput: ou
// $arg=Make, [<, '$argfile', >, "out"put, cat, -e, >, ou ] ->		filesnames:[Makefile, output, ou], input: Makefile, ouput: ou

t_cmd *create_cmd(char **line)
{
	t_cmd *cmd;
	static int i;
	int end;
	int start;
	char *tmp;

	if (line == NULL)
		return (NULL);
	cmd = malloc(sizeof(t_cmd));
	if (cmd == NULL)
		return (NULL);
	i = 0;
	while (line[i])
	{
		end = 0;
		if (ft_strcmp(line[i], "|") == 0)
			i++;
		else if (ft_strcmp(line[i], "<") == 0)
		{
			// i++;
			// if (line[i][end] == '\'')
			// {
			// 	end++;
				
			// }
			// else if (line[i][end] == '"')
			// {
			// 	end++;
			// 	while (line[i][end] && line[i][end] != '"')
			// 	{
					
			// 	}
			// }
		}
		else if (ft_strcmp(line[i], ">") == 0)
		{
			
		}
		else if (ft_strcmp(line[i], ">>") == 0)
		{
			
		}
		else if (ft_strcmp(line[i], "<<") == 0)
		{
			
		}
		i++;
	}
}

char *filtre_quote(char *str)
{
	int i;
	int start;
	char *tmp;
	char *tmp1;
	char *str_filter;

	str_filter = NULL;
	tmp = NULL;
	i = 0;
	while (str && str[i])
	{
		if (str[i] == '\'')
			quote_skip(str, &i, &tmp, '\'');
		else if (str[i] == '"')
			quote_skip(str, &i, &tmp, '"');
		else
		{
			start = i;
			while (str[i] && str[i] != '\'' && str[i] != '"')
				i++;
			free(tmp);
			tmp = ft_substr(str, start, i - start);
			printf("\e[31mtmp:|%s|\e[0m\n", tmp);
		}
		tmp1 = str_filter;
		str_filter = ft_strjoin(str_filter, tmp);
		free(tmp1);
	}
	return (str_filter);
}