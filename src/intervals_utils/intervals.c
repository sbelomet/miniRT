/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intervals.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbelomet <sbelomet@42lausanne.ch>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/23 10:17:51 by sbelomet          #+#    #+#             */
/*   Updated: 2024/05/28 13:02:32 by sbelomet         ###   ########.fr       */
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

t_inter	ft_inter_new2(const t_inter a, const t_inter b)
{
	t_inter	inter;

	if (a.min <= b.min)
		inter.min = a.min;
	else
		inter.min = b.min;
	if (a.max >= b.max)
		inter.max = a.max;
	else
		inter.max = b.max;
	return (inter);
}
