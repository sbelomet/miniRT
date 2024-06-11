/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   base_init.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgosselk <lgosselk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/22 09:47:15 by lgosselk          #+#    #+#             */
/*   Updated: 2024/06/07 13:53:59 by lgosselk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	set_base(t_base *base)
{
	reset_select(base, 0);
	base->alloc = NULL;
	base->exit_code = 0;
	base->camera = NULL;
	base->alight = NULL;
	base->mlx_ptr = NULL;
	base->win_ptr = NULL;
	base->num_of_lights = 0;
	base->first_light = NULL;
	base->first_object = NULL;
	base->image.img_ptr = NULL;
	base->image.img_data = NULL;
	base->seed = (unsigned long)&base;
}

int	ft_create_image(t_base *base)
{
	base->image.img_ptr = mlx_new_image(base->mlx_ptr, WIN_WIDTH, WIN_HEIGHT);
	if (!base->image.img_ptr)
		return (print_error(IMG_ERR, NULL, 1), set_exit_code(base, 1, 1));
	base->image.img_data = mlx_get_data_addr(base->image.img_ptr,
			&base->image.bitsperpix, &base->image.size_line,
			&base->image.endian);
	return (0);
}

int	ft_base_init(t_base *base)
{
	base->mlx_ptr = mlx_init();
	if (!base->mlx_ptr)
		return (print_error(MLX_ERR, NULL, 1), set_exit_code(base, 1, 1));
	base->win_ptr = mlx_new_window(base->mlx_ptr, WIN_WIDTH, WIN_HEIGHT, TITLE);
	if (!base->win_ptr)
		return (print_error(WIN_ERR, NULL, 1), set_exit_code(base, 1, 1));
	return (0);
}
