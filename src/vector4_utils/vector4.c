/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector4.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbelomet <sbelomet@42lausanne.ch>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/20 15:44:42 by scherty           #+#    #+#             */
/*   Updated: 2024/05/28 13:00:59 by sbelomet         ###   ########.fr       */
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
/* 
t_vector4	ft_set_face_normal(const t_ray r, const t_vector4 outward_normal,
				t_hit_rec *rec)
{
	rec->front_face = ft_vec3_dot(r.dir, outward_normal) < 0;
	if (rec->front_face)
		return (outward_normal);
	else
		return (ft_vec3_mult(outward_normal, -1));
} */

int	ft_vec4_near_zero(const t_vector4 v)
{
	double	s;

	s = 1e-8;
	return ((fabs(v.x) < s) && (fabs(v.y) < s) && (fabs(v.z) < s)
		&& (fabs(v.w) < s));
}
