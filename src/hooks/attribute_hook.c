/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   attribute_hook.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgosselk <lgosselk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/07 11:42:19 by lgosselk          #+#    #+#             */
/*   Updated: 2024/06/07 14:13:06 by lgosselk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

bool	add_to_sphere(t_sphere *sphere, int type)
{
	if (type == PLUS_KEY)
		sphere->diam = sphere->diam + 0.5;
	else if (sphere->diam >= 0.5)
		sphere->diam = sphere->diam - 0.5;
	sphere->radius = sphere->diam / 2;
	sphere->tm.scaling = mtrx_scaling(ft_vec3_new(sphere->radius,
				sphere->radius, sphere->radius));
	ft_gtf_set_transform(&sphere->tm, sphere->tm.translation,
		sphere->tm.rotation, sphere->tm.scaling);
	printf("Diameter of sphere increased: %lf\n", sphere->diam);
	return (true);
}

bool	add_to_cylinder(t_cylin *cylinder, int type, int mode)
{
	if (type == PLUS_KEY)
	{
		if (mode == HEIGHT)
			cylinder->height = cylinder->height + 0.5;
		else if (mode == WIDTH)
		{
			cylinder->diam = cylinder->diam + 0.5;
			cylinder->radius = cylinder->diam / 2;
		}
	}
	else
	{
		if (mode == HEIGHT && cylinder->height >= 0.5)
			cylinder->height = cylinder->height - 0.5;
		else if (mode == WIDTH && cylinder->height >= 0.5)
		{
			cylinder->diam = cylinder->diam - 0.5;
			cylinder->radius = cylinder->diam / 2;
		}
	}
	cylinder->tm.scaling = mtrx_scaling(ft_vec3_new(cylinder->radius,
				cylinder->radius, cylinder->height));
	ft_gtf_set_transform(&cylinder->tm, cylinder->tm.translation,
		cylinder->tm.rotation, cylinder->tm.scaling);
	return (printf("Attributes of cylinder modified\n"), true);
}

bool	add_to_cone(t_cone *cone, int type, int mode)
{
	if (type == PLUS_KEY)
	{
		if (mode == HEIGHT)
			cone->height = cone->height + 0.5;
		else if (mode == WIDTH)
		{
			cone->diam = cone->diam + 0.5;
			cone->radius = cone->diam / 2;
		}
	}
	else
	{
		if (mode == HEIGHT && cone->height >= 0.5)
			cone->height = cone->height - 0.5;
		else if (mode == WIDTH && cone->diam >= 0.5)
		{
			cone->diam = cone->diam - 0.5;
			cone->radius = cone->diam / 2;
		}
	}
	cone->tm.scaling = mtrx_scaling(ft_vec3_new(cone->radius,
				cone->radius, cone->height));
	ft_gtf_set_transform(&cone->tm, cone->tm.translation, cone->tm.rotation,
		cone->tm.scaling);
	return (printf("Attributes of cone modified\n"), true);
}

void	modify_value(t_base *base, int type)
{
	t_objects	*objs;
	bool		modified;

	modified = false;
	objs = base->first_object;
	base->select.modified = true;
	while (objs)
	{
		if (objs->id == base->select.id && objs->type == SPHERE)
			modified = add_to_sphere((t_sphere *)objs->object, type);
		if (objs->id == base->select.id && objs->type == CYLINDER)
			modified = add_to_cylinder((t_cylin *)objs->object, type,
					base->select.cylin_cone_modes);
		if (objs->id == base->select.id && objs->type == CONE)
			modified = add_to_cone((t_cone *)objs->object, type,
					base->select.cylin_cone_modes);
		if (modified)
		{
			base->select.modified = true;
			return ;
		}
		objs = objs->next;
	}
}
