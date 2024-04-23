/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbelomet <sbelomet@42lausanne.ch>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/23 10:21:25 by sbelomet          #+#    #+#             */
/*   Updated: 2024/04/23 14:51:36 by sbelomet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_color	ft_color_new(const double a, const double r,
	const double g, const double b)
{
	t_color	color;

	color.alpha = a;
	color.red = r;
	color.green = g;
	color.blue = b;
	return (color);
}

double	ft_linear_to_gamma(double linear_component)
{
	if (linear_component > 0)
		return (sqrt(linear_component));
	return (0);
}

int	ft_get_color_int(t_color color)
{
	int		cints[4];
	t_inter	intensity;

	color.red = ft_linear_to_gamma(color.red);
	color.green = ft_linear_to_gamma(color.green);
	color.blue = ft_linear_to_gamma(color.blue);
	intensity = ft_inter_new(0.000, 0.999);
	cints[0] = (int)(256 * ft_inter_clamp(intensity, color.alpha));
	cints[1] = (int)(256 * ft_inter_clamp(intensity, color.red));
	cints[2] = (int)(256 * ft_inter_clamp(intensity, color.green));
	cints[3] = (int)(256 * ft_inter_clamp(intensity, color.blue));
	return (cints[0] << 24 | cints[1] << 16 | cints[2] << 8 | cints[3]);
}
