/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   filter.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achakkaf <achakkaf@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/06 17:05:59 by achakkaf          #+#    #+#             */
/*   Updated: 2024/06/08 11:17:06 by achakkaf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

// char *single_quote(char *part, t_parsing_info *info)
// {
// 	info->end++;
// 	info->start = info->end;
// 	while (part[info->end] && part[info->end] != '\'')
// 		info->end++;
// 	return (ft_substr(part, info->start, info->end++ - info->start));
// }

// char *double_without(char *part, t_parsing_info *info, int flage)
// {
// 	char *var_value;
// 	char *string;
// 	char *tmp;

// 	string = NULL;
// 	var_value = NULL;
// 	info->start = info->end;
// 	while (part[info->end])
// 	{
// 		if (flage == DOUBLE_Q && part[info->end] == '"')
// 			break;
// 		else if (flage != DOUBLE_Q && (part[info->end] == '"' || part[info->end] == '\''))
// 			break;
// 		if (part[info->end] == '$')
// 			var_value = dollar_sign(part, info, var_value);
// 		else
// 			info->end++;
// 	}
// 	tmp = ft_substr(part, info->start, info->end - info->start);
// 	string = ft_strjoin(var_value, tmp);
// 	free(tmp);
// 	free(var_value);
// 	return (string);
// }

// char *filter(char *part, t_parsing_info *info)
// {
// 	char *tmp;
// 	char *tmp_free;
// 	char *token;

// 	info->end = 0;
// 	token = NULL;
// 	while (part && part[info->end])
// 	{
// 		if (part[info->end] == '\'')
// 			tmp = single_quote(part, info);
// 		else if (part[info->end] == '"')
// 		{
// 			info->end++;
// 			tmp = double_without(part, info, DOUBLE_Q);
// 			info->end++;
// 		}
// 		else
// 			tmp = double_without(part, info, -22);
// 		tmp_free = token;
// 		token = ft_strjoin(token, tmp);
// 		free(tmp_free);
// 		free(tmp);
// 		tmp = NULL;
// 	}
// 	return (token);
// }
