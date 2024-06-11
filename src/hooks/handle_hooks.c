/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_hooks.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgosselk <lgosselk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/07 12:50:48 by lgosselk          #+#    #+#             */
/*   Updated: 2024/06/07 14:13:33 by lgosselk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	reset_select(t_base *base, int flag)
{
	base->select.id = -1;
	base->select.type = -1;
	base->select.modified = false;
	base->select.cylin_cone_modes = -1;
	base->select.in_translation = false;
	if (flag)
		printf("Deselected object, camera or light\n");
}

void	ft_handle_control(t_base *base)
{
	if (base->select.id == -1)
		printf("Before, you must select an object\n");
	else
	{
		if (base->select.in_translation)
			printf("Translation mode disable\n");
		else
			printf("Translation mode enable\n");
		base->select.in_translation = !base->select.in_translation;
	}
}

void	ft_new_render(t_base *base)
{
	ft_render(base);
	base->select.modified = false;
}

int	key_hook(int keycode, t_base *base)
{
	if (keycode == ESC_KEY)
		close_window(base);
	if (keycode == DESELECT_KEY)
		reset_select(base, 1);
	if (keycode == PLUS_KEY && ft_check_types(base, MODIF_ATTRI))
		modify_value(base, PLUS_KEY);
	if (keycode == MINUS_KEY && ft_check_types(base, MODIF_ATTRI))
		modify_value(base, MINUS_KEY);
	if (ft_rotable_keys(keycode) && base->select.id != -1)
		ft_rotate(base, base->first_object, keycode);
	if (keycode == TAB_KEY && ft_check_types(base, SWITCH))
		switching_cylin_cone_mode(base);
	if (keycode == CONTROL_LEFT || keycode == CONTROL_RIGHT)
		ft_handle_control(base);
	if (keycode == CAMERA_SELECT)
		ft_handle_control(base);
	if (keycode == LIGHT_SELECT && base->first_light)
		ft_handle_light(base);
	if (base->select.in_translation && (keycode == ARROW_UP
			|| keycode == ARROW_DOWN))
		ft_handle_distance(base, base->first_object, keycode);
	if ((keycode == RENDER_KEY && base->select.modified))
		ft_new_render(base);
	return (1);
}

void	ft_hooks(t_base *base)
{
	mlx_hook(base->win_ptr, 2, (1L << 0), key_hook, base);
	mlx_hook(base->win_ptr, 4, (1L << 2), button_hook, base);
	mlx_hook(base->win_ptr, 17, (1L << 17), close_window, base);
	mlx_loop(base->mlx_ptr);
}
