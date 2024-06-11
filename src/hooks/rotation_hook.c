/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rotation_hook.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgosselk <lgosselk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/07 11:42:29 by lgosselk          #+#    #+#             */
/*   Updated: 2024/06/07 14:16:09 by lgosselk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

bool	ft_rotation_plane(t_plane *plane, int keycode)
{
	t_matrix	new_rotation;

	new_rotation = ft_new_rotation_matrix(keycode);
	plane->tm.rotation = ft_mtrx_mult_mtrx(plane->tm.rotation,
			new_rotation);
	ft_gtf_set_transform(&plane->tm, plane->tm.translation,
		plane->tm.rotation, plane->tm.scaling);
	return (true);
}

bool	ft_rotation_cylinder(t_cylin *cylinder, int keycode)
{
	t_matrix	new_rotation;

	new_rotation = ft_new_rotation_matrix(keycode);
	cylinder->tm.rotation = ft_mtrx_mult_mtrx(cylinder->tm.rotation,
			new_rotation);
	ft_gtf_set_transform(&cylinder->tm, cylinder->tm.translation,
		cylinder->tm.rotation, cylinder->tm.scaling);
	return (true);
}

bool	ft_rotation_cone(t_cone *cone, int keycode)
{
	t_matrix	new_rotation;

	new_rotation = ft_new_rotation_matrix(keycode);
	cone->tm.rotation = ft_mtrx_mult_mtrx(cone->tm.rotation,
			new_rotation);
	ft_gtf_set_transform(&cone->tm, cone->tm.translation,
		cone->tm.rotation, cone->tm.scaling);
	return (true);
}

bool	ft_rotation_camera(t_base *base, int keycode)
{
	(void)base;
	(void)keycode;
	return (false);
}

void	ft_rotate(t_base *base, t_objects *objs, int keycode)
{
	bool	modified;

	modified = false;
	if (base->select.id == -1)
		return ;
	if (base->select.id == -2 && base->select.type == CAMERA)
		modified = ft_rotation_camera(base, keycode);
	while (objs)
	{
		if (objs->id == base->select.id && objs->type == PLANE)
			modified = ft_rotation_plane((t_plane *)objs->object, keycode);
		if (objs->id == base->select.id && objs->type == CYLINDER)
			modified = ft_rotation_cylinder((t_cylin *)objs->object, keycode);
		if (objs->id == base->select.id && objs->type == CONE)
			modified = ft_rotation_cone((t_cone *)objs->object, keycode);
		if (modified)
		{
			base->select.modified = true;
			printf("Rotation object has been modified\n");
			return ;
		}
		objs = objs->next;
	}
}
