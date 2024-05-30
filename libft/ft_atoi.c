/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Achakkaf <zizcarschak1@gmail.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/07 17:55:29 by Achakkaf          #+#    #+#             */
/*   Updated: 2023/12/25 11:53:40 by Achakkaf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	whitespace(const char *str)
{
	int	i;

	i = 0;
	while ((str[i] >= 9 && str[i] <= 13) || str[i] == 32)
		i++;
	return (i);
}

static int	nmber(const char *str, long long res, int sign)
{
	long long	cpy;

	while (*str)
	{
		if (*str >= '0' && *str <= '9')
		{
			cpy = res;
			res = res * 10 + *str - '0';
			if (sign == -1 && res < cpy)
				return (0);
			if (sign == 1 && res < cpy)
				return (-1);
			str++;
		}
		else
			return (res * sign);
	}
	return (res * sign);
}

int	ft_atoi(const char *str)
{
	int			sign;
	long long	res;

	res = 0;
	sign = 1;
	str += whitespace(str);
	if (*str == '-')
	{
		sign = -1;
		str++;
	}
	else if (*str == '+')
		str++;
	res = nmber(str, res, sign);
	return ((int)res);
}
