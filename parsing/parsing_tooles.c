/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_tooles.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achakkaf <achakkaf@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/01 17:50:44 by achakkaf          #+#    #+#             */
/*   Updated: 2024/06/01 19:22:27 by achakkaf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

int check_name(char *name)
{
	int i;

	i = 0;
	if (name && ft_isdigit(name[i]) == GOOD)
		return (ERROR);
	while (name && name[i])
	{
		if (ft_isalpha(name[i]) == ERROR && ft_isdigit(name[i]) == ERROR && name[i] != '_')
			return (ERROR);
		i++;
	}
	return (GOOD);
}

char *var_name(char *token)
{
	int end;

	end = 0;
	if (token && ft_isdigit(token[end]) == GOOD)
		return (NULL);
	while (token && token[end])
	{
		if (ft_isalpha(token[end]) == ERROR && ft_isdigit(token[end]) == ERROR && token[end] != '_')
			break;
		end++;
	}
	return (ft_substr(token, 0, end));
}

char *single_q_filter(char *token, int start)
{
	int end;
	
	end = start;
	while (token && token[end] && token[end] != '\'')
		end++;
	return (ft_substr(token , start, end - start));
}
