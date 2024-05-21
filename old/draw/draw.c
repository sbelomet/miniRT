/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbelomet <sbelomet@42lausanne.ch>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/19 15:08:51 by sbelomet          #+#    #+#             */
/*   Updated: 2024/04/30 12:59:08 by sbelomet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	ft_pixel_put(t_base *base, int x, int y, int color)
{
	int	pos;

	pos = (x * base->image.bitsperpix / 8) + (y * base->image.size_line);
	if (x >= 0 && y >= 0 && x < WIN_WIDTH && y < WIN_HEIGHT)
		*(int *) &base->image.img_data[pos] = color;
}

void	ft_render(t_base *base)
{
	int			index[3];
	t_color		c;
	t_ray		r;

	index[1] = -1;
	while (++index[1] < WIN_HEIGHT)
	{
		index[0] = -1;
		printf("Scanlines remaining: %d\n", WIN_HEIGHT - index[1]);
		while (++index[0] < WIN_WIDTH)
		{
			c = ft_color_new(0, 0, 0, 0);
			index[2] = -1;
			while (++index[2] < SAMPLE_PPIXEL)
			{
				r = ft_ray_calculate(base, index[0], index[1]);
				c = ft_color_add(c,
						ft_ray_color(base, r, MAX_DEPTH, base->first_object));
			}
			ft_pixel_put(base, index[0], index[1], ft_get_color_int(
					ft_color_mult(c, PIX_SAMPLE_SCALE)));
		}
		mlx_put_image_to_window(base->mlx_ptr, base->win_ptr,
			base->image.img_ptr, 0, 0);
	}
}
