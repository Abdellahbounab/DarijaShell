/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   var_extend.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achakkaf <achakkaf@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/07 11:20:15 by achakkaf          #+#    #+#             */
/*   Updated: 2024/06/07 11:35:07 by achakkaf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

// line: cat -e $arg"hello" '$arg2' "$AR" -> string : cat -e Makefile"hello" 'file2' "ls -la"
// line: $Ar -> <hello>out cat -e | NOT WORKING AAHHHHHAHAH

// char *var_extand_string(char *line)
// {
// 	t_parsing_info *info;
// 	// int end;
// 	// int start;
// 	char *string;
// 	char *tmp;
// 	char *var_name;
// 	char *var_value;
// 	if (line == NULL)
// 		return (NULL);
// 	info = malloc(sizeof(t_parsing_info));
// 	if (info == NULL)
// 		return (NULL);
// 	string = NULL;
// 	info->end = 0;
// 	while (line && line[info->end])
// 	{
// 		info->end = info->start;
// 		while(line[info->end] && line[info->end] != '$')
// 			info->end++;
// 		string = ft_substr(line, info->start, info->end - info->start);
// 		if (line[info->end] == '$')
// 		{
// 			var_name = get_var_name(line, info);
// 			// var_value = 
// 		}
// 	}
// 	return (string);
// }
