/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector3.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbelomet <sbelomet@42lausanne.ch>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/20 15:44:42 by scherty           #+#    #+#             */
/*   Updated: 2024/05/28 13:00:59 by sbelomet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_vector3	ft_vec3_new(const double x, const double y, const double z)
{
	t_vector3	v;

	v.x = x;
	v.y = y;
	v.z = z;
	return (v);
}

void	ft_vec3_print(const t_vector3 v, const char *name)
{
	printf("Vector3 %s(x:%f, y:%f, z:%f)\n", name, v.x, v.y, v.z);
}
/* 
t_vector3	ft_set_face_normal(const t_ray r, const t_vector3 outward_normal,
				t_hit_rec *rec)
{
	rec->front_face = ft_vec3_dot(r.dir, outward_normal) < 0;
	if (rec->front_face)
		return (outward_normal);
	else
		return (ft_vec3_mult(outward_normal, -1));
} */

int	ft_vec3_near_zero(const t_vector3 v)
{
	double	s;

	s = 1e-8;
	return ((fabs(v.x) < s) && (fabs(v.y) < s) && (fabs(v.z) < s));
}
