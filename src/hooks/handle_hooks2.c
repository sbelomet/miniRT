/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_hooks2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgosselk <lgosselk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/07 12:50:42 by lgosselk          #+#    #+#             */
/*   Updated: 2024/06/07 14:14:27 by lgosselk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

bool	ft_check_types(t_base *base, int type)
{
	if (base->select.id <= 0)
		return (false);
	if (type == SWITCH)
	{
		if (base->select.type == CONE || base->select.type == CYLINDER)
			return (true);
	}
	if (type == MODIF_ATTRI)
	{
		if (base->select.type == CONE || base->select.type == CYLINDER
			|| base->select.type == SPHERE)
			return (true);
	}
	return (false);
}

void	ft_handle_light(t_base *base)
{
	if (base->select.type == LIGHT)
	{
		if (base->select.id < base->num_of_lights
			&& base->num_of_lights > 1)
		{
			base->select.id = base->select.id + 1;
			printf("light with id: %d selected\n", base->select.id);
		}
		else if (base->select.id == base->num_of_lights
			&& base->num_of_lights > 1)
		{
			printf("light with id: 1 selected\n");
			base->select.id = 1;
		}
		else
			printf("Only one light available\n");
	}
	else if (base->num_of_lights != 0)
	{
		reset_select(base, 0);
		printf("light with id: 1 selected\n");
		base->select.id = 1;
		base->select.type = LIGHT;
	}
}

void	ft_handle_camera(t_base *base)
{
	if (base->select.type == CAMERA)
		printf("Camera is already selected\n");
	else
	{
		reset_select(base, 0);
		printf("Camera selected\n");
		base->select.type = CAMERA;
		base->select.id = -2;
	}
}

void	switching_cylin_cone_mode(t_base *base)
{
	if (base->select.cylin_cone_modes == HEIGHT)
	{
		base->select.cylin_cone_modes = WIDTH;
		printf("cylinder mode modification switched to width\n");
	}
	else
	{
		base->select.cylin_cone_modes = HEIGHT;
		printf("cylinder mode modification switched to height\n");
	}
}
