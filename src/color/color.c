/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbelomet <sbelomet@42lausanne.ch>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/19 15:08:59 by sbelomet          #+#    #+#             */
/*   Updated: 2024/04/19 15:09:35 by sbelomet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int	ft_get_color(double a, double r, double g, double b)
{
	int	ia;
	int	ir;
	int	ig;
	int	ib;

	ia = (int)a;
	ir = (int)(255.99 * r);
	ig = (int)(255.99 * g);
	ib = (int)(255.99 * b);

	return (ia << 24 | ir << 16 | ig << 8 | ib);
}
