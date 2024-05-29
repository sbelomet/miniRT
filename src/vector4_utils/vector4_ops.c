/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector4_ops.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbelomet <sbelomet@42lausanne.ch>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/17 14:26:35 by scherty           #+#    #+#             */
/*   Updated: 2024/05/29 12:00:40 by sbelomet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_vector4	ft_vec4_mult_mtrx(const t_vector4 v, const t_matrix m)
{
	t_vector4	res;

	res.x = v.x * m.m[0][0] + v.y * m.m[0][1]
		+ v.z * m.m[0][2] + v.w * m.m[0][3];
	res.y = v.x * m.m[1][0] + v.y * m.m[1][1]
		+ v.z * m.m[1][2] + v.w * m.m[1][3];
	res.z = v.x * m.m[2][0] + v.y * m.m[2][1]
		+ v.z * m.m[2][2] + v.w * m.m[2][3];
	res.w = v.x * m.m[3][0] + v.y * m.m[3][1]
		+ v.z * m.m[3][2] + v.w * m.m[3][3];
	return (res);
}
