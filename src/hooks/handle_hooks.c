/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_hooks.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbelomet <sbelomet@42lausanne.ch>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/07 12:50:48 by lgosselk          #+#    #+#             */
/*   Updated: 2024/05/28 13:01:35 by sbelomet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int	key_hook(int keycode, t_base *base)
{
	if (keycode == 53)
		close_window(base);
	printf("keycode: %d\n", keycode);
	return (1);
}

int	button_hook(int buttoncode, int x, int y, t_base *base)
{
	(void)base;
	(void)buttoncode;
	printf("pos: x:%d and y:%d\n", x, y);
	return (1);
}

void	ft_hooks(t_base *base)
{
	mlx_hook(base->win_ptr, 2, (1L << 0), key_hook, base);
	mlx_hook(base->win_ptr, 4, (1L << 2), button_hook, base);
	mlx_hook(base->win_ptr, 17, (1L << 0), close_window, base);
	mlx_loop(base->mlx_ptr);
}
