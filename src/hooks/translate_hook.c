/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   translate_hook.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgosselk <lgosselk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/07 11:42:39 by lgosselk          #+#    #+#             */
/*   Updated: 2024/06/07 14:21:32 by lgosselk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

bool	translate_cone(t_cone *cone, double x, double y)
{
	t_matrix	new_trans;

	new_trans = to_translate(x, y, cone->coord.z);
	cone->tm.translation = ft_mtrx_mult_mtrx(cone->tm.translation,
			new_trans);
	ft_gtf_set_transform(&cone->tm, cone->tm.translation,
		cone->tm.rotation, cone->tm.scaling);
	return (true);
}

bool	translate_cylinder(t_cylin *cylinder, double x, double y)
{
	t_matrix	new_trans;

	new_trans = to_translate(x, y, cylinder->coord.z);
	cylinder->tm.translation = ft_mtrx_mult_mtrx(cylinder->tm.translation,
			new_trans);
	ft_gtf_set_transform(&cylinder->tm, cylinder->tm.translation,
		cylinder->tm.rotation, cylinder->tm.scaling);
	return (true);
}

bool	translate_camera(t_base *base, double x, double y)
{
	(void)base;
	(void)x;
	(void)y;
	return (false);
}

bool	translate_light(t_base *base, double x, double y)
{
	t_light		*light;
	double		world_x;
	double		world_y;
	t_vector3	new_pos;

	light = base->first_light;
	while (light)
	{
		if (base->select.id == light->id)
		{
			world_x = (x * (1.0 / ((double)WIN_WIDTH / 2.0))) - 1.0;
			world_y = (y * (1.0 / ((double)WIN_HEIGHT / 2.0))) - 1.0;
			new_pos = ft_vec3_new(world_x, world_y, light->coord.z);
			light->coord = new_pos;
			return (true);
		}
		light = light->next;
	}
	return (false);
}

void	ft_translate(t_base *base, t_objects *objs, double x, double y)
{
	bool	modified;

	modified = false;
	if (base->select.id == -2 && base->select.type == CAMERA)
		modified = translate_camera(base, x, y);
	if (base->select.id > 0 && base->select.type == LIGHT)
		modified = translate_light(base, x, y);
	while (objs)
	{
		if (objs->id == base->select.id && objs->type == SPHERE)
			modified = translate_sphere((t_sphere *)objs->object, x, y);
		if (objs->id == base->select.id && objs->type == PLANE)
			modified = translate_plane((t_plane *)objs->object, x, y);
		if (objs->id == base->select.id && objs->type == CYLINDER)
			modified = translate_cylinder((t_cylin *)objs->object, x, y);
		if (objs->id == base->select.id && objs->type == CONE)
			modified = translate_cone((t_cone *)objs->object, x, y);
		if (modified)
		{
			base->select.modified = true;
			return ;
		}
		objs = objs->next;
	}
}
