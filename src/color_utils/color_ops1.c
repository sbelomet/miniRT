/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color_ops1.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbelomet <sbelomet@42lausanne.ch>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/23 10:21:36 by sbelomet          #+#    #+#             */
/*   Updated: 2024/05/28 12:59:26 by sbelomet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_color	ft_color_add(t_color c1, const t_color c2)
{
	c1.alpha += c2.alpha;
	c1.red += c2.red;
	c1.green += c2.green;
	c1.blue += c2.blue;
	return (c1);
}

t_color	ft_color_sub(t_color c1, const t_color c2)
{
	c1.alpha -= c2.alpha;
	c1.red -= c2.red;
	c1.green -= c2.green;
	c1.blue -= c2.blue;
	return (c1);
}

t_color	ft_color_mult(t_color c, const double value)
{
	c.alpha *= value;
	c.red *= value;
	c.green *= value;
	c.blue *= value;
	return (c);
}

t_color	ft_color_div(t_color c, const double value)
{
	c.alpha /= value;
	c.red /= value;
	c.green /= value;
	c.blue /= value;
	return (c);
}

t_color	ft_color_mult_color(t_color c1, const t_color c2)
{
	c1.alpha *= c2.alpha;
	c1.red *= c2.red;
	c1.green *= c2.green;
	c1.blue *= c2.blue;
	return (c1);
}
