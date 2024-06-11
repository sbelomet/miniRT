/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gtform_ops.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgosselk <lgosselk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/17 14:47:37 by scherty           #+#    #+#             */
/*   Updated: 2024/06/07 12:45:38 by lgosselk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_matrix	mtrx_transpose(t_matrix	t)
{
	size_t		row;
	size_t		col;
	t_matrix	table;

	row = -1;
	while (++row < 4)
	{
		col = -1;
		while (++col < 4)
			table.m[col][row] = t.m[row][col];
	}
	return (table);
}

t_matrix	mtrx_translate(t_vector3 coord)
{
	t_matrix	table;

	table = ft_mtrx_new();
	table.m[0][3] = coord.x;
	table.m[1][3] = coord.y;
	table.m[2][3] = coord.z;
	return (table);
}

t_matrix	mtrx_scaling(t_vector3 scale)
{
	t_matrix	table;

	table = ft_mtrx_new();
	table.m[0][0] = scale.x;
	table.m[1][1] = scale.y;
	table.m[2][2] = scale.z;
	return (table);
}

t_gtform	ft_gtf_mult(const t_gtform g1, const t_gtform g2)
{
	t_gtform	gt;

	gt.fwdtfm = ft_mtrx_mult_mtrx(g1.fwdtfm, g2.fwdtfm);
	gt.bcktfm = ft_mtrx_inverse(gt.fwdtfm);
	return (gt);
}
