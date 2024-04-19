/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbelomet <sbelomet@42lausanne.ch>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/19 15:08:51 by sbelomet          #+#    #+#             */
/*   Updated: 2024/04/19 15:24:13 by sbelomet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	ft_pixel_put(t_base *base, int x, int y, int color)
{
	int	pos;

	pos = (x * base->bitsperpix / 8) + (y * base->size_line);
	if (x >= 0 && y >= 0 && x < WIN_WIDTH && y < WIN_HEIGHT)
		*(int *) &base->img_data[pos] = color;
}

void	ft_draw_base_texture(t_base *base)
{
	int	i;
	int	j;
	int	c;

	c = 0;
	i = 0;
	while (i < WIN_WIDTH)
	{
		j = 0;
		while (j < WIN_HEIGHT)
		{
			c = ft_get_color(0, ((double)i / (WIN_WIDTH)),
					((double)j / (WIN_HEIGHT)), 0);
			ft_pixel_put(base, i, j, c);
			j++;
		}
		i++;
	}
	mlx_put_image_to_window(base->mlx_ptr, base->win_ptr, base->img_ptr, 0, 0);
}
