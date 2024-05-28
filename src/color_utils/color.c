/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbelomet <sbelomet@42lausanne.ch>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/23 10:21:25 by sbelomet          #+#    #+#             */
/*   Updated: 2024/05/28 12:59:59 by sbelomet         ###   ########.fr       */
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

t_color	ft_color_byte_to_per(const t_color color)
{
	t_color	new_c;

	new_c.alpha = color.alpha / 256;
	new_c.red = color.red / 256;
	new_c.green = color.green / 256;
	new_c.blue = color.blue / 256;
	return (new_c);
}

void	ft_color_print(const t_color c, const char *name)
{
	printf("Color %s(a:%f, r:%f, g:%f, b:%f)\n", name,
		c.alpha, c.red, c.green, c.blue);
}
