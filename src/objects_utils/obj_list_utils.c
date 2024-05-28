/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   obj_list_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbelomet <sbelomet@42lausanne.ch>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/09 14:24:54 by sbelomet          #+#    #+#             */
/*   Updated: 2024/05/28 13:00:59 by sbelomet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_objects	*ft_object_new(void *object, int type)
{
	t_objects	*new;

	new = (t_objects *)malloc(sizeof(t_objects));
	if (!new)
		return (NULL);
	new->object = object;
	new->next = NULL;
	ft_set_hit_func(new, type);
	return (new);
}

t_objects	*ft_object_last(t_objects *hittable)
{
	t_objects	*last;

	last = hittable;
	if (!last)
		return (NULL);
	while (last->next)
		last = last->next;
	return (last);
}

void	ft_object_add(t_objects **hittable, t_objects *new)
{
	t_objects	*last;

	if (!*hittable)
	{
		*hittable = new;
		return ;
	}
	last = ft_object_last(*hittable);
	new->id = last->id;
	last->next = new;
}

void	ft_set_hit_func(t_objects *new_object, int type)
{
	if (type == SPHERE)
		new_object->ft_hit = ft_sphere_hit;
	else if (type == PLANE)
		new_object->ft_hit = ft_plane_hit;
	else if (type == CYLINDER)
		new_object->ft_hit = ft_cylinder_hit;
	else if (type == CONE)
		new_object->ft_hit = ft_cone_hit;
}
