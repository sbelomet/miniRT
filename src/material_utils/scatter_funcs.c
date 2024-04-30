/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scatter_funcs.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbelomet <sbelomet@42lausanne.ch>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/24 10:08:49 by sbelomet          #+#    #+#             */
/*   Updated: 2024/04/30 12:51:08 by sbelomet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int	ft_lamb_scatter(const t_ray r_in, const t_hit_rec rec,
	t_color *attenuation, t_ray *scattered)
{
	t_vector3	scatter_direction;

	scatter_direction = ft_vec3_add(rec.normal, ft_vec3_rand_unit(rec.base));
	if (ft_vec3_near_zero(scatter_direction))
		scatter_direction = rec.normal;
	*scattered = ft_ray_new(rec.p, scatter_direction);
	*attenuation = rec.mat->albedo;
	(void)r_in;
	return (true);
}

int	ft_metal_scatter(const t_ray r_in, const t_hit_rec rec,
	t_color *attenuation, t_ray *scattered)
{
	t_vector3	reflected;

	reflected = ft_vec3_add(ft_vec3_unit(ft_reflect(r_in.dir, rec.normal)),
			ft_vec3_mult(ft_vec3_rand_unit(rec.base), rec.mat->fuzz));
	*scattered = ft_ray_new(rec.p, reflected);
	*attenuation = rec.mat->albedo;
	return (ft_vec3_dot(scattered->dir, rec.normal) > 0);
}

int	ft_dielectric_scatter(const t_ray r_in, const t_hit_rec rec,
	t_color *attenuation, t_ray *scattered)
{
	double		ri;
	t_vector3	unit_direction;
	t_vector3	refracted;

	*attenuation = ft_color_new(0, 1, 1, 1);
	if (rec.front_face)
		ri = rec.mat->ref_index;
	else
		ri = 1.0 / rec.mat->ref_index;
	unit_direction = ft_vec3_unit(r_in.dir);
	refracted = ft_refract(unit_direction, rec.normal, ri);
	*scattered = ft_ray_new(rec.p, refracted);
	return (true);
}
