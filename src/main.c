/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbelomet <sbelomet@42lausanne.ch>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/14 10:10:13 by lgosselk          #+#    #+#             */
/*   Updated: 2024/04/25 15:25:54 by sbelomet         ###   ########.fr       */
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

t_hittable	*ft_hittables_init(t_base *base)
{
/* 	t_hittable	*h1;
	t_hittable	*h2;
	t_hittable	*h3;
	t_hittable	*h4;
	t_sphere	*s1;
	t_sphere	*s2;
	t_sphere	*s3;
	t_sphere	*s4;

	h1 = (t_hittable *)malloc(sizeof(t_hittable));
	h2 = (t_hittable *)malloc(sizeof(t_hittable));
	h3 = (t_hittable *)malloc(sizeof(t_hittable));
	h4 = (t_hittable *)malloc(sizeof(t_hittable));
	s1 = (t_sphere *)malloc(sizeof(t_sphere));
	s2 = (t_sphere *)malloc(sizeof(t_sphere));
	s3 = (t_sphere *)malloc(sizeof(t_sphere));
	s4 = (t_sphere *)malloc(sizeof(t_sphere));
	h1->object = s1;
	h1->next = h2;
	h2->object = s2;
	h2->next = h3;
	h3->object = s3;
	h3->next = h4;
	h4->object = s4;
	h4->next = NULL;
	s1->center = ft_vec3_new(0, -100.5, -1);
	s1->radius = 100;
	s1->mat = ft_mat_new(LAMBERTIAN, ft_color_new(0, .8, .8, 0),
			ft_lamb_scatter);
	s2->center = ft_vec3_new(0, 0, -1.2);
	s2->radius = .5;
	s2->mat = ft_mat_new(LAMBERTIAN, ft_color_new(0, .1, .2, .5),
			ft_lamb_scatter);
	s3->center = ft_vec3_new(-1, 0, -1);
	s3->radius = .5;
	s3->mat = ft_mat_new(METAL, ft_color_new(0, .8, .8, .8),
			ft_metal_scatter);
	s4->center = ft_vec3_new(1, 0, -1);
	s4->radius = .5;
	s4->mat = ft_mat_new(METAL, ft_color_new(0, .8, .6, .2),
			ft_metal_scatter);
	s4->mat->fuzz = .5;
 */
	
	t_hittable	*h_head;
	t_sphere	*s;

	h_head = NULL;
	s = (t_sphere *)malloc(sizeof(t_sphere));
	s->center = ft_vec3_new(0, -1000, 0);
	s->radius = 1000;
	s->mat = ft_mat_new(LAMBERTIAN, ft_color_new(0, .5, .5, .5), ft_lamb_scatter);
	ft_hittable_add(&h_head, ft_hittable_new(s));
	for (int i = -11; i < 11; i++)
	{
		for (int j = -11; j < 11; j++)
		{
			double choose_mat = ft_rand_double(base);
			t_vector3 center = ft_vec3_new(i + .9 * ft_rand_double(base), .2, j + .9 * ft_rand_double(base));
			if (ft_vec3_len(ft_vec3_sub(center, ft_vec3_new(4, .2, 0))) > .9)
			{
				t_sphere *s = (t_sphere *)malloc(sizeof(t_sphere));
				if (choose_mat < .8)
				{
					t_color albedo = ft_color_mult_color(ft_color_new(0, ft_rand_double(base), ft_rand_double(base), ft_rand_double(base)), ft_color_new(0, ft_rand_double(base), ft_rand_double(base), ft_rand_double(base)));
					s->center = center;
					s->radius = .2;
					s->mat = ft_mat_new(LAMBERTIAN, albedo, ft_lamb_scatter);
				}
				else
				{
					t_color albedo = ft_color_new(0, ft_rand_double_range(base, .5, 1), ft_rand_double_range(base, .5, 1), ft_rand_double_range(base, .5, 1));
					double fuzz = ft_rand_double_range(base, 0, .5);
					s->center = center;
					s->radius = .2;
					s->mat = ft_mat_new(METAL, albedo, ft_metal_scatter);
					s->mat->fuzz = fuzz;
				}
				ft_hittable_add(&h_head, ft_hittable_new(s));
			}
		}
	}
	s = (t_sphere *)malloc(sizeof(t_sphere));
	s->center = ft_vec3_new(-4, 1, 0);
	s->radius = 1;
	s->mat = ft_mat_new(METAL, ft_color_new(0, .3, .9, .6), ft_metal_scatter);
	s->mat->fuzz = .2;
	ft_hittable_add(&h_head, ft_hittable_new(s));
	s = (t_sphere *)malloc(sizeof(t_sphere));
	s->center = ft_vec3_new(0, 1, 0);
	s->radius = 1;
	s->mat = ft_mat_new(LAMBERTIAN, ft_color_new(0, .4, .2, .9), ft_lamb_scatter);
	ft_hittable_add(&h_head, ft_hittable_new(s));
	s = (t_sphere *)malloc(sizeof(t_sphere));
	s->center = ft_vec3_new(4, 1, 0);
	s->radius = 1;
	s->mat = ft_mat_new(METAL, ft_color_new(0, 1, 1, .9), ft_metal_scatter);
	s->mat->fuzz = 0;
	ft_hittable_add(&h_head, ft_hittable_new(s));
	return (h_head);
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
	base.camera = ft_camera_init(20);
    base.first_hittable = ft_hittables_init(&base);
	ft_render(&base);
	//mlx_hook(base.win_ptr, 2, (1L << 0), key_hook, &base);
	mlx_hook(base.win_ptr, 17, (1L << 0), close_window, &base);
	mlx_loop(base.mlx_ptr);
	return (EXIT_SUCCESS);
}
