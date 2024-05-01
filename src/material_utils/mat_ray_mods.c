/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mat_ray_mods.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbelomet <sbelomet@42lausanne.ch>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/30 12:49:52 by sbelomet          #+#    #+#             */
/*   Updated: 2024/05/01 10:15:05 by sbelomet         ###   ########.fr       */
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
/* 
t_color	ft_emmited(double u, double v, const t_vector3 p)
{
	return 
}
 */