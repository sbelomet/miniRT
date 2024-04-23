/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intervals.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbelomet <sbelomet@42lausanne.ch>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/23 10:17:51 by sbelomet          #+#    #+#             */
/*   Updated: 2024/04/23 10:17:52 by sbelomet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_inter	ft_inter_new(const double min, const double max)
{
	t_inter	inter;

	inter.min = min;
	inter.max = max;
	return (inter);
}

int	ft_inter_contains(const t_inter inter, const double x)
{
	if (inter.min <= x && x <= inter.max)
		return (true);
	return (false);
}

int	ft_inter_surrounds(const t_inter inter, const double x)
{
	if (inter.min < x && x < inter.max)
		return (true);
	return (false);
}

double	ft_inter_clamp(const t_inter inter, const double x)
{
	if (x < inter.min)
		return (inter.min);
	if (x > inter.max)
		return (inter.max);
	return (x);
}
