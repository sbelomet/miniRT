/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   translate_z_hook.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgosselk <lgosselk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/07 13:29:29 by lgosselk          #+#    #+#             */
/*   Updated: 2024/06/07 14:20:38 by lgosselk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

bool	trans_z_sphere(t_sphere *sphere, int keycode)
{
	t_matrix	new_trans;

	if (keycode == ARROW_UP)
		new_trans = to_translate(sphere->center.x,
				sphere->center.y, sphere->center.z - 0.25);
	else
		new_trans = to_translate(sphere->center.x,
				sphere->center.y, sphere->center.z + 0.25);
	sphere->tm.translation = ft_mtrx_mult_mtrx(sphere->tm.translation,
			new_trans);
	ft_gtf_set_transform(&sphere->tm, sphere->tm.translation,
		sphere->tm.rotation, sphere->tm.scaling);
	return (true);
}

bool	trans_z_plane(t_plane *plane, int keycode)
{
	t_matrix	new_trans;

	if (keycode == ARROW_UP)
		new_trans = to_translate(plane->coord.x,
				plane->coord.y, plane->coord.z - 0.25);
	else
		new_trans = to_translate(plane->coord.x,
				plane->coord.y, plane->coord.z + 0.25);
	plane->tm.translation = ft_mtrx_mult_mtrx(plane->tm.translation,
			new_trans);
	ft_gtf_set_transform(&plane->tm, plane->tm.translation,
		plane->tm.rotation, plane->tm.scaling);
	return (true);
}

bool	trans_z_cylinder(t_cylin *cylinder, int keycode)
{
	t_matrix	new_trans;

	if (keycode == ARROW_UP)
		new_trans = to_translate(cylinder->coord.x,
				cylinder->coord.y, cylinder->coord.z - 0.25);
	else
		new_trans = to_translate(cylinder->coord.x,
				cylinder->coord.y, cylinder->coord.z + 0.25);
	cylinder->tm.translation = ft_mtrx_mult_mtrx(cylinder->tm.translation,
			new_trans);
	ft_gtf_set_transform(&cylinder->tm, cylinder->tm.translation,
		cylinder->tm.rotation, cylinder->tm.scaling);
	return (true);
}

bool	trans_z_cone(t_cone *cone, int keycode)
{
	t_matrix	new_trans;

	if (keycode == ARROW_UP)
		new_trans = to_translate(cone->coord.x,
				cone->coord.y, cone->coord.z - 0.25);
	else
		new_trans = to_translate(cone->coord.x,
				cone->coord.y, cone->coord.z + 0.25);
	cone->tm.translation = ft_mtrx_mult_mtrx(cone->tm.translation,
			new_trans);
	ft_gtf_set_transform(&cone->tm, cone->tm.translation,
		cone->tm.rotation, cone->tm.scaling);
	return (true);
}

void	ft_handle_distance(t_base *base, t_objects *objs, int keycode)
{
	bool	modified;

	modified = false;
	if (base->select.id == -2 && base->select.type == CAMERA)
		modified = trans_z_camera(base, keycode);
	if (base->select.id > 0 && base->select.type == LIGHT)
		modified = trans_z_light(base, keycode);
	while (objs)
	{
		if (objs->id == base->select.id && objs->type == SPHERE)
			modified = trans_z_sphere((t_sphere *)objs->object, keycode);
		if (objs->id == base->select.id && objs->type == PLANE)
			modified = trans_z_plane((t_plane *)objs->object, keycode);
		if (objs->id == base->select.id && objs->type == CYLINDER)
			modified = trans_z_cylinder((t_cylin *)objs->object, keycode);
		if (objs->id == base->select.id && objs->type == CONE)
			modified = trans_z_cone((t_cone *)objs->object, keycode);
		if (modified)
		{
			base->select.modified = true;
			printf("Distance object have been modified\n");
			return ;
		}
		objs = objs->next;
	}
}
