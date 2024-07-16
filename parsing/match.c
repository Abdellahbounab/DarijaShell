/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   match.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achakkaf <achakkaf@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/09 12:10:49 by achakkaf          #+#    #+#             */
/*   Updated: 2024/07/16 10:08:05 by achakkaf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

bool	handle_quotes(const char **pattern, \
	bool *is_single_q, bool *is_double_q)
{
	if (**pattern == '"')
	{
		*is_double_q = !*is_double_q;
		(*pattern)++;
		return (true);
	}
	else if (**pattern == '\'')
	{
		*is_single_q = !*is_single_q;
		(*pattern)++;
		return (true);
	}
	return (false);
}

bool	handle_wildcard(char **filename, const char **pattern)
{
	while (*(*pattern + 1) == '*')
		(*pattern)++;
	if (*(*pattern + 1) == '\0')
		return (true);
	while (**filename)
	{
		if (match(*filename, *pattern + 1))
			return (true);
		(*filename)++;
	}
	return (false);
}

bool	match_chars(char **filename, const char **pattern)
{
	if (**pattern != **filename)
		return (false);
	(*filename)++;
	(*pattern)++;
	return (true);
}

void	skip_star(const char **pattern)
{
	while (**pattern == '*')
		(*pattern)++;
}

bool	match(char *filename, const char *pattern)
{
	while (*filename && *pattern)
	{
		if (*pattern == '*')
		{
			if (handle_wildcard(&filename, &pattern))
				return (true);
			return (false);
		}
		if (!match_chars(&filename, &pattern))
			return (false);
	}
	skip_star(&pattern);
	return (*pattern == '\0' && *filename == '\0');
}
