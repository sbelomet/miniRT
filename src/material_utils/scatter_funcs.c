/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scatter_funcs.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbelomet <sbelomet@42lausanne.ch>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/24 10:08:49 by sbelomet          #+#    #+#             */
/*   Updated: 2024/04/24 14:03:14 by sbelomet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_vector3	ft_reflect(const t_vector3 v, const t_vector3 n)
{
	return (ft_vec3_sub(v, ft_vec3_mult(n, 2 * ft_vec3_dot(v, n))));
}

t_vector3	ft_refract(const t_vector3 uv,
	const t_vector3 n, double etai_over_etat)
{
	double		cos_theta;
	t_vector3	r_out_perp;
	t_vector3	r_out_parallel;

	cos_theta = fmin(ft_vec3_dot(ft_vec3_mult(uv, -1), n), 1);
	r_out_perp = ft_vec3_mult(ft_vec3_add(uv, ft_vec3_mult(
					n, cos_theta)), etai_over_etat);
	r_out_parallel = ft_vec3_mult(n, -sqrt(fabs(
					1.0 - ft_vec3_len_squared(r_out_perp))));
	return (ft_vec3_add(r_out_perp, r_out_parallel));
}

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
