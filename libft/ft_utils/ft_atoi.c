/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgosselk <lgosselk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/24 13:51:45 by lgosselk          #+#    #+#             */
/*   Updated: 2024/01/18 10:20:35 by lgosselk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

static int	ft_whitespace(char c)
{
	if (c == ' ' || c == '\t' || c == '\n'
		|| c == '\v' || c == '\f' || c == '\r')
		return (1);
	return (0);
}

static int	ft_sign(char c)
{
	if (c == 45 || c == 43)
		return (1);
	return (0);
}

static int	ft_number(char c)
{
	if (c >= 48 && c <= 57)
		return (1);
	return (0);
}

int	ft_atoi(const char *nptr)
{
	int		i;
	int		sign;
	char	*ptr;
	int		result;

	i = 0;
	sign = 1;
	result = 0;
	ptr = (char *)nptr;
	while (ft_whitespace(ptr[i]))
		i++;
	if (ft_sign(ptr[i]))
	{
		if (ptr[i] == 45)
			sign *= -1;
		i++;
	}
	while (ft_number(ptr[i]))
	{
		result = (result * 10) + (ptr[i] - '0');
		i++;
	}
	return (result * sign);
}
