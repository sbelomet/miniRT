/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector3.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbelomet <sbelomet@42lausanne.ch>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/20 15:44:42 by scherty           #+#    #+#             */
/*   Updated: 2024/04/23 11:18:11 by sbelomet         ###   ########.fr       */
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

t_vector3	ft_set_face_normal(const t_ray r, const t_vector3 outward_normal)
{
	if (ft_vec3_dot(r.dir, outward_normal) < 0)
		return (outward_normal);
	else
		return (ft_vec3_mult(outward_normal, -1));
}
