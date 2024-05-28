/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbelomet <sbelomet@42lausanne.ch>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/19 15:08:51 by sbelomet          #+#    #+#             */
/*   Updated: 2024/05/28 13:00:06 by sbelomet         ###   ########.fr       */
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
	int			index[2];
	double		fact_xy[2];
	t_ray		r;
	t_hit_rec	rec;

	rec.base = base;
	fact_xy[0] = 1.0 / ((double)WIN_WIDTH / 2.0);
	fact_xy[1] = 1.0 / ((double)WIN_HEIGHT / 2.0);
	r = ft_ray_new(ft_vec3_new(0, 0, 0), ft_vec3_new(0, 0, 0));
	index[1] = -1;
	while (++index[1] < WIN_HEIGHT)
	{
		index[0] = -1;
		printf("Scanlines remaining: %d\n\033[1A\033[2K", WIN_HEIGHT - index[1]);
		while (++index[0] < WIN_WIDTH)
		{
			ft_generate_ray(*base->camera, ((double)index[0] * fact_xy[0]) - 1.0, ((double)index[1] * fact_xy[1]) - 1.0, &r);
			if (ft_anything_hit(base->first_object, r, &rec))
			{
				rec.color = rec.mat->ft_comp_color(base->first_object, &rec, base->first_light);
				ft_pixel_put(base, index[0], index[1], ft_get_color_int(rec.color));
			}
		}
		mlx_put_image_to_window(base->mlx_ptr, base->win_ptr,
			base->image.img_ptr, 0, 0);
	}
	printf("Done!\n");
}
