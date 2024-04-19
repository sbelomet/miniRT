/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgosselk <lgosselk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/25 11:20:32 by lgosselk          #+#    #+#             */
/*   Updated: 2024/01/18 10:20:39 by lgosselk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

static int	ft_nbrlen(long nbr)
{
	int	i;

	i = 0;
	if (nbr < 0)
	{
		nbr *= -1;
		i++;
	}
	while (nbr != 0)
	{
		nbr = nbr / 10;
		i++;
	}
	return (i);
}

static void	ft_putnbr_mod(long nbr, char *str, int *i)
{
	if (nbr >= 10)
	{
		ft_putnbr_mod(nbr / 10, str, i);
		ft_putnbr_mod(nbr % 10, str, i);
	}
	else
		str[(*i)++] = nbr + '0';
}

char	*ft_itoa(int n)
{
	int		i;
	long	nbr;
	char	*str;

	nbr = n;
	if (nbr == 0)
		return (ft_strdup("0"));
	else
		str = (char *) malloc((ft_nbrlen(nbr) + 1) * sizeof(char));
	if (str == NULL)
		return (NULL);
	i = 0;
	if (nbr < 0)
	{
		str[i++] = '-';
		nbr *= -1;
	}
	ft_putnbr_mod(nbr, str, &i);
	str[i] = '\0';
	return (str);
}
