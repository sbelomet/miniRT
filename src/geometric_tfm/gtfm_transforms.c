/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gtfm_transforms.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgosselk <lgosselk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/14 14:35:25 by sbelomet          #+#    #+#             */
/*   Updated: 2024/06/07 14:26:01 by lgosselk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	ft_gtf_set_transform(t_gtform *gt, const t_matrix trans,
	const t_matrix rot_mtrx, const t_matrix scale)
{
	gt->fwdtfm = ft_mtrx_mult_mtrx(trans, ft_mtrx_mult_mtrx(rot_mtrx, scale));
	gt->bcktfm = ft_mtrx_inverse(gt->fwdtfm);
	gt->transpose = mtrx_transpose(gt->bcktfm);
}

t_vector3	ft_gtf_apply_vec3(const t_gtform gt, const t_vector3 v,
	const int dir_flag)
{
	t_vector4	tmp_vec;

	tmp_vec = ft_vec4_new(v.x, v.y, v.z, 1);
	if (dir_flag)
		tmp_vec = ft_vec4_mult_mtrx(tmp_vec, gt.fwdtfm);
	else
		tmp_vec = ft_vec4_mult_mtrx(tmp_vec, gt.bcktfm);
	return (ft_vec3_new(tmp_vec.x, tmp_vec.y, tmp_vec.z));
}

t_ray	ft_gtf_apply_ray(const t_gtform gt, const t_ray r, const int dir_flag)
{
	t_ray	out_ray;

	out_ray.p1 = ft_gtf_apply_vec3(gt, r.p1, dir_flag);
	out_ray.p2 = ft_gtf_apply_vec3(gt, r.p2, dir_flag);
	out_ray.lab = ft_vec3_sub(out_ray.p2, out_ray.p1);
	return (out_ray);
}
