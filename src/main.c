/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbelomet <sbelomet@42lausanne.ch>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/14 10:10:13 by lgosselk          #+#    #+#             */
/*   Updated: 2024/04/19 15:16:47 by sbelomet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_base	ft_base_init(void)
{
	t_base	base;

	base.mlx_ptr = mlx_init();
	if (!base.mlx_ptr)
		ft_error("MLX initialisation failure");
	base.win_ptr = mlx_new_window(base.mlx_ptr, WIN_WIDTH, WIN_HEIGHT, TITLE);
	if (!base.win_ptr)
		ft_error("Window initialisation failure");
	base.img_ptr = mlx_new_image(base.mlx_ptr, WIN_WIDTH, WIN_HEIGHT);
	if (!base.img_ptr)
		ft_error("Image initialisation failure");
	base.img_data = mlx_get_data_addr(base.img_ptr, &base.bitsperpix,
			&base.size_line, &base.endian);
	return (base);
}

int	main(int argc, char **argv)
{
	t_base	base;

	base = ft_base_init();
	ft_draw_base_texture(&base);
	mlx_loop(base.mlx_ptr);
	(void)argc;
	(void)argv;
}
