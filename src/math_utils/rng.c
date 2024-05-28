/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rng.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbelomet <sbelomet@42lausanne.ch>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/23 10:17:37 by sbelomet          #+#    #+#             */
/*   Updated: 2024/05/28 13:00:59 by sbelomet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	ft_srand(t_base *base, unsigned long new_seed)
{
	base->seed = new_seed;
}

unsigned long	ft_rand(t_base *base)
{
	base->seed = (1103515245 * base->seed + 12345) % 2147483648;
	return (base->seed);
}

double	ft_rand_double_range(t_base *base, double min, double max)
{
	double	scale;

	scale = (double)ft_rand(base) / (double)2147483648;
	return (min + scale * (max - min));
}

double	ft_rand_double(t_base *base)
{
	return (ft_rand_double_range(base, 0, 1));
}
