/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector4.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgosselk <lgosselk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/20 15:44:42 by scherty           #+#    #+#             */
/*   Updated: 2024/06/07 14:30:04 by lgosselk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_vector4	ft_vec4_new(const double x, const double y, const double z,
	const double w)
{
	t_vector4	v;

	v.x = x;
	v.y = y;
	v.z = z;
	v.w = w;
	return (v);
}

void	ft_vec4_print(const t_vector4 v, const char *name)
{
	printf("Vector4 %s(x:%f, y:%f, z:%f, w:%f)\n", name, v.x, v.y, v.z, v.w);
}

int	ft_vec4_near_zero(const t_vector4 v)
{
	double	s;

	s = 1e-8;
	return ((fabs(v.x) < s) && (fabs(v.y) < s) && (fabs(v.z) < s)
		&& (fabs(v.w) < s));
}
