/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   translate_z_hook2.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgosselk <lgosselk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/07 13:29:29 by lgosselk          #+#    #+#             */
/*   Updated: 2024/06/07 14:21:09 by lgosselk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

bool	trans_z_camera(t_base *base, int keycode)
{
	(void)base;
	(void)keycode;
	return (false);
}

bool	trans_z_light(t_base *base, int keycode)
{
	t_light		*light;
	t_vector3	new_pos;

	light = base->first_light;
	while (light)
	{
		if (base->select.id == light->id)
		{
			if (keycode == ARROW_UP)
				new_pos = ft_vec3_new(light->coord.x,
						light->coord.y, light->coord.z - 0.25);
			else
				new_pos = ft_vec3_new(light->coord.x,
						light->coord.y, light->coord.z + 0.25);
			light->coord = new_pos;
			return (true);
		}
		light = light->next;
	}
	return (false);
}
