/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcards_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achakkaf <achakkaf@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/25 10:54:21 by achakkaf          #+#    #+#             */
/*   Updated: 2024/06/27 13:06:35 by achakkaf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing_bonus.h"

/*
• find all the maches files name
• sort them by name
*/

char **get_files(void)
{
	DIR *dir;
	struct dirent *file;
	char **filenames;

	dir = opendir("."); // PWD
	if (dir == NULL)
		return (NULL);
	file = readdir(dir);
	while (file)
	{
		if (file->d_name[0] != '.')
			filenames = append_array(filenames, file->d_name);
		file = readdir(dir);
	}
	return (filenames);
}

/*
	• *.c: all files end with .c
	• *: all files exept for those who start with .
	• str*: all file that start with str
	• *str*: all file that str part of
	• etc …
*/

bool match(char *filename, const char *pattern)
{
	bool is_single_q;
	bool is_double_q;

	is_single_q = false;
	is_double_q = false;
	while (*filename && *pattern)
	{
		if (!is_single_q && !is_double_q)
		{
			if (*pattern == '"')
			{
				is_double_q = true;
				pattern++;
				continue;
			}
			else if (*pattern == '\'')
			{
				is_single_q = true;
				pattern++;
				continue;
			}
			else if (*pattern == '*')
			{
				while (*(pattern + 1) == '*')
					pattern++;
				if (*(pattern + 1) == '\0')
					return (true);
				while (*filename)
				{
					if (match(filename, pattern + 1))
						return (true);
					filename++;
				}
				return (false);
			}
		}
		if (*pattern == '"')
		{
			is_double_q = false;
			pattern++;
			continue;
		}
		else if (*pattern == '\'')
		{
			is_single_q = false;
			pattern++;
			continue;
		}
		if (*pattern != *filename)
			return (false);
		filename++;
		pattern++;
	}
	while (*pattern == '*')
		pattern++;
	return (*pattern == '\0' && *filename == '\0');
}

char **wildcard(char **filenames, char *pattern)
{
	int i;
	char **result;

	i = 0;
	result = NULL;
	while (filenames && filenames[i])
	{
		if (match(filenames[i], pattern))
			result = append_array(result, filenames[i]);
		i++;
	}
	if (result == NULL)
		result = append_array(result, pattern);
	return (result);
}
/*
	array1: {"hello 1", "how", "are", "you", NULL}
	array2: {"good", "thanks", NULL}
*/
char **join_arrays(char **dst_array, char **src_array)
{
	int i;

	if (dst_array == NULL && src_array == NULL)
		return (NULL);
	if (dst_array == NULL)
		return (src_array);
	if (src_array == NULL)
		return ( dst_array);
	i = 0;
	while (src_array[i])
	{
		dst_array = append_array(dst_array, src_array[i]);
		i++;
	}
	free(&src_array);
	return (dst_array);
}

char **add_wildcard(char **split)
{
	int i;
	char **result;
	char **filenames;
	char **tmp;

	i = 0;
	filenames = get_files();
	result = NULL;
	while (split[i])
	{
		if (ft_strchr(split[i], '*'))
		{
			tmp = wildcard(filenames, split[i]);
			result = join_arrays(result, tmp);
		}
		else
			result = append_array(result, split[i]);
		i++;
	}
	return (result);
}
