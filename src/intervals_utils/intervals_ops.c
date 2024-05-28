/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intervals_ops.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbelomet <sbelomet@42lausanne.ch>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/30 10:08:44 by sbelomet          #+#    #+#             */
/*   Updated: 2024/05/28 13:02:28 by sbelomet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

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

t_inter	ft_inter_expand(const t_inter inter, const double delta)
{
	double	padding;

	padding = delta / 2;
	return (ft_inter_new(inter.min - padding, inter.max + padding));
}
