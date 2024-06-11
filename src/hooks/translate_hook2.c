/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   translate_hook2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgosselk <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/07 11:47:09 by lgosselk          #+#    #+#             */
/*   Updated: 2024/06/07 11:47:11 by lgosselk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_matrix	to_translate(double x, double y, double z)
{
	double		world_x;
	double		world_y;
	t_vector3	new_pos;

	world_x = (x * (1.0 / ((double)WIN_WIDTH / 2.0))) - 1.0;
	world_y = (y * (1.0 / ((double)WIN_HEIGHT / 2.0))) - 1.0;
	new_pos = ft_vec3_new(world_x, world_y, z);
	return (mtrx_translate(new_pos));
}

bool	translate_sphere(t_sphere *sphere, double x, double y)
{
	t_matrix	new_trans;

	new_trans = to_translate(x, y, sphere->center.z);
	sphere->tm.translation = ft_mtrx_mult_mtrx(sphere->tm.translation,
			new_trans);
	ft_gtf_set_transform(&sphere->tm, sphere->tm.translation,
		sphere->tm.rotation, sphere->tm.scaling);
	return (true);
}

bool	translate_plane(t_plane *plane, double x, double y)
{
	t_matrix	new_trans;

	new_trans = to_translate(x, y, plane->coord.z);
	plane->tm.translation = ft_mtrx_mult_mtrx(plane->tm.translation,
			new_trans);
	ft_gtf_set_transform(&plane->tm, plane->tm.translation,
		plane->tm.rotation, plane->tm.scaling);
	return (true);
}
