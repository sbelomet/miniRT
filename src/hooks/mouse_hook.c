/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouse_hook.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgosselk <lgosselk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/07 12:46:32 by lgosselk          #+#    #+#             */
/*   Updated: 2024/06/10 11:25:25 by lgosselk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	ft_setup_selected(t_base *base)
{
	if (base->select.type == SPHERE)
		printf("Sphere selected\n");
	if (base->select.type == PLANE)
		printf("Plane selected\n");
	if (base->select.type == CYLINDER || base->select.type == CONE)
	{
		if (base->select.type == CYLINDER)
			printf("Cylinder selected, mode Height selected by default\n");
		else
			printf("Cone selected, mode Height selected by default\n");
		base->select.cylin_cone_modes = HEIGHT;
	}
}

bool	select_object(t_base *base, int x, int y)
{
	t_ray		ray;
	t_hit_rec	rec;

	ft_generate_ray(*base->camera, x, y, &ray);
	if (!ft_anything_hit(base->first_object, ray, &rec))
		return (false);
	if (base->select.id == rec.object->id)
	{
		printf("Already selected\n");
		return (true);
	}
	base->select.id = rec.object->id;
	base->select.type = rec.object->type;
	ft_setup_selected(base);
	return (true);
}

void	ft_handle_select(t_base *base, int x, int y)
{
	if (select_object(base, x, y))
		printf("Object with id is selected: %d\n", base->select.id);
	else
	{
		printf("Reseting object selection\n");
		reset_select(base, 0);
	}
}

int	button_hook(int buttoncode, int x, int y, t_base *base)
{
	if (!base->select.in_translation && buttoncode == 1
		&& (x >= 0 && x <= WIN_WIDTH) && (y >= 0 && y <= WIN_HEIGHT))
		ft_handle_select(base, x, y);
	else if (base->select.in_translation && (x >= 0 && x <= WIN_WIDTH)
		&& (y >= 0 && y <= WIN_HEIGHT) && buttoncode == CLICK_LEFT)
		ft_translate(base, base->first_object, x, y);
	if (base->select.modified && base->select.in_translation
		&& buttoncode == 1)
		ft_new_render(base);
	return (1);
}
