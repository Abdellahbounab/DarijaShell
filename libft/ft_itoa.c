/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Achakkaf <zizcarschak1@gmail.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/11 18:39:44 by Achakkaf          #+#    #+#             */
/*   Updated: 2023/12/21 10:26:06 by Achakkaf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	length(long n)
{
	int	count;

	count = 0;
	if (n == 0)
		return (1);
	while (n > 0)
	{
		count++;
		n /= 10;
	}
	return (count);
}

static char	*copy(int count, int sign, char *str, long c)
{
	str[count--] = '\0';
	while (count >= 0)
	{
		str[count] = c % 10 + '0';
		if (sign && count == 0)
			str[count] = '-';
		count--;
		c /= 10;
	}
	return (str);
}

char	*ft_itoa(int n)
{
	char	*str;
	int		count;
	int		sign;
	long	c;

	c = n;
	sign = 0;
	if (c < 0)
	{
		c = -c;
		sign = 1;
	}
	count = length(c);
	if (sign)
		count++;
	str = malloc(sizeof(char) * (count + 1));
	if (!str)
		return (NULL);
	str = copy(count, sign, str, c);
	return (str);
}
