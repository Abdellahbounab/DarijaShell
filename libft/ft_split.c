/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abounab <abounab@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/12 09:41:34 by Achakkaf          #+#    #+#             */
/*   Updated: 2024/06/21 20:40:56 by abounab          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	cwords(const char *s, char c)
{
	int	i;
	int	count;
	int	inword;

	i = 0;
	inword = 1;
	count = 0;
	while (s[i])
	{
		while (s[i] == c && s[i])
			i++;
		while (s[i] != c && s[i])
		{
			if (inword)
			{
				count++;
				inword = 0;
			}
			i++;
		}
		inword = 1;
	}
	return (count);
}

static char	*mysubstr(const char *s, int start, int len)
{
	int		i;
	char	*str;

	i = 0;
	str = malloc(sizeof(char) * (len + 1));
	if (str)
	{
		while (i < len)
		{
			str[i] = s[start + i];
			i++;
		}
		str[i] = '\0';
	}
	return (str);
}

static char	**ft_free(char **strings, int i)
{
	int	j;

	j = 0;
	if (strings)
	{
		while (j <= i)
		{
			free(strings[j]);
			j++;
		}
		free(strings);
	}
	return (NULL);
}

static char	**splitp1(char **strings, const char *s, char c)
{
	int		i;
	int		j;
	int		s_i;

	s_i = 0;
	i = 0;
	strings = ft_calloc(cwords(s, c) + 1, sizeof(char *));
	while (s[i] && strings)
	{
		while (s[i] == c && s[i])
			i++;
		j = i;
		if (!s[i])
			break ;
		while (s[i] != c && s[i])
			i++;
		strings[s_i] = mysubstr(s, j, i - j);
		if (!(strings[s_i]))
			return (ft_free(strings, s_i));
		s_i++;
	}
	return (strings);
}

char	**ft_split(const char *s, char c)
{
	char	**strings;

	strings = NULL;
	if (!s)
		return (NULL);
	strings = splitp1(strings, s, c);
	return (strings);
}
