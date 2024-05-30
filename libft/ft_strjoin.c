/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Achakkaf <zizcarschak1@gmail.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/08 11:30:04 by Achakkaf          #+#    #+#             */
/*   Updated: 2024/03/27 19:42:58 by Achakkaf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*store;
	int		i;

	i = 0;
	if (!s1 && !s2)
		return (NULL);
	else if (!s1)
		return (ft_strdup(s2));
	else if (!s2)
		return (ft_strdup(s1));
	store = malloc((ft_strlen(s1) + ft_strlen(s2) + 1) * sizeof(char));
	if (!store)
		return (NULL);
	while (*s1)
		store[i++] = *(s1++);
	while (*s2)
		store[i++] = *(s2++);
	store[i] = '\0';
	return (store);
}
