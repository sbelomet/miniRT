/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbelomet <sbelomet@42lausanne.ch>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/19 15:08:51 by sbelomet          #+#    #+#             */
/*   Updated: 2024/05/30 10:02:19 by sbelomet         ###   ########.fr       */
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

static void	ft_comp_mat_put_pix(t_base *base, t_hit_rec rec, int x, int y)
{
	rec.mat->ft_comp_color(base->first_object,
		&rec, base->first_light, &rec.color);
	ft_pixel_put(base, x, y, ft_get_color_int(rec.color));
}

void	ft_render(t_base *base)
{
	int			x;
	int			y;
	t_ray		ray;
	t_hit_rec	rec;

	rec.base = base;
	y = -1;
	while (++y < WIN_HEIGHT)
	{
		x = -1;
		printf("Scanlines remaining: %d\n\033[1A\033[2K", WIN_HEIGHT - y);
		while (++x < WIN_WIDTH)
		{
			ft_generate_ray(*base->camera, x, y, &ray);
			if (ft_anything_hit(base->first_object, ray, &rec))
				ft_comp_mat_put_pix(base, rec, x, y);
		}
	}
	mlx_put_image_to_window(base->mlx_ptr, base->win_ptr,
		base->image.img_ptr, 0, 0);
	printf("Done!\n");
}
