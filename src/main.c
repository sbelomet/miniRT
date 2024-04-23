/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbelomet <sbelomet@42lausanne.ch>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/14 10:10:13 by lgosselk          #+#    #+#             */
/*   Updated: 2024/04/23 12:54:19 by sbelomet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static int	check_args(int argc, char **argv)
{
	char	*extension;

	if (argc != 2 || !argv[1])
		return (print_error(BAD_ARGS, NULL, 0));
	extension = ft_strrchr(argv[1], '.');
	if (!extension || !ft_equal_strs(extension, ".rt"))
		return (print_error(EXT_ERR, NULL, 0));
	return (1);
}

t_camera	ft_camera_init(void)
{
	t_camera	cam;
	t_vector3	viewport_u;
	t_vector3	viewport_v;
	t_vector3	viewport_upper_left;

	cam.origin = ft_vec3_new(0, 0, 0);
	cam.ori = ft_vec3_new(0, 0, 1);
	viewport_u = ft_vec3_new(VIEWPORT_WIDTH, 0, 0);
	viewport_v = ft_vec3_new(0, -VIEWPORT_HEIGHT, 0);
	cam.pixel_delta_u = ft_vec3_div(viewport_u, WIN_WIDTH);
	cam.pixel_delta_v = ft_vec3_div(viewport_v, WIN_HEIGHT);
	viewport_upper_left = ft_vec3_sub(ft_vec3_sub(
				ft_vec3_sub(cam.origin, cam.ori),
				ft_vec3_div(viewport_u, 2)),
			ft_vec3_div(viewport_v, 2));
	cam.pixel00_loc = ft_vec3_add(ft_vec3_mult(ft_vec3_add(
					cam.pixel_delta_u, cam.pixel_delta_v), .5),
			viewport_upper_left);
	return (cam);
}

t_hittable	*ft_hittables_init(void)
{
	t_hittable	*h1;
	t_hittable	*h2;
	t_hittable	*h3;
	t_sphere	*s1;
	t_sphere	*s2;
	t_sphere	*s3;

	h1 = (t_hittable *)malloc(sizeof(t_hittable));
	h2 = (t_hittable *)malloc(sizeof(t_hittable));
	h3 = (t_hittable *)malloc(sizeof(t_hittable));
	s1 = (t_sphere *)malloc(sizeof(t_sphere));
	s2 = (t_sphere *)malloc(sizeof(t_sphere));
	s3 = (t_sphere *)malloc(sizeof(t_sphere));
	h1->object = s1;
	h1->next = h2;
	h2->object = s2;
	h2->next = h3;
	h3->object = s3;
	h3->next = NULL;
	s1->center = ft_vec3_new(0, 0, -1);
	s1->radius = .5;
	s1->color = ft_color_new(0, .2, .9, 1);
	s2->center = ft_vec3_new(0, -100.5, -1);
	s2->radius = 100;
	s2->color = ft_color_new(0, 1, .1, 1);
	s3->center = ft_vec3_new(100, 50, -100);
	s3->radius = 25;
	s3->color = ft_color_new(0, .5, .3, .8);
	return (h1);
}

int	main(const int argc, char **argv)
{
	t_base	base;

	if (!check_args(argc, argv))
		return (EXIT_FAILURE);
	set_base(&base);
	//if (file_parse(&base, argv[1]) == 1)
	//	on_destroy(&base);
	if (ft_base_init(&base) == 1)
		on_destroy(&base);
	base.camera = ft_camera_init();
	base.first_hittable = ft_hittables_init();
	ft_render(&base);
	//mlx_hook(base.win_ptr, 2, (1L << 0), key_hook, &base);
	mlx_hook(base.win_ptr, 17, (1L << 0), close_window, &base);
	mlx_loop(base.mlx_ptr);
	return (EXIT_SUCCESS);
}
