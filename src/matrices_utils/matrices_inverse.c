/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrices_inverse.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbelomet <sbelomet@42lausanne.ch>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/16 10:02:07 by sbelomet          #+#    #+#             */
/*   Updated: 2024/05/28 13:00:59 by sbelomet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static void	dets3x3_cont(const t_matrix m, double *dets3x3, double *dets2x2)
{
	dets3x3[8] = m.m[0][0] * dets2x2[15] - m.m[0][1] * dets2x2[13]
		+ m.m[0][2] * dets2x2[12];
	dets3x3[9] = m.m[0][0] * dets2x2[16] - m.m[0][1] * dets2x2[14]
		+ m.m[0][3] * dets2x2[12];
	dets3x3[10] = m.m[0][0] * dets2x2[17] - m.m[0][2] * dets2x2[14]
		+ m.m[0][3] * dets2x2[13];
	dets3x3[11] = m.m[0][1] * dets2x2[17] - m.m[0][2] * dets2x2[16]
		+ m.m[0][3] * dets2x2[15];
	dets3x3[12] = m.m[1][0] * dets2x2[15] - m.m[1][1] * dets2x2[13]
		+ m.m[1][2] * dets2x2[12];
	dets3x3[13] = m.m[1][0] * dets2x2[16] - m.m[1][1] * dets2x2[14]
		+ m.m[1][3] * dets2x2[12];
	dets3x3[14] = m.m[1][0] * dets2x2[17] - m.m[1][2] * dets2x2[14]
		+ m.m[1][3] * dets2x2[13];
	dets3x3[15] = m.m[1][1] * dets2x2[17] - m.m[1][2] * dets2x2[16]
		+ m.m[1][3] * dets2x2[15];
}

static void	ft_mtrx_get_dets3x3(const t_matrix m, double *dets3x3,
	double *dets2x2)
{
	dets3x3[0] = m.m[0][0] * dets2x2[5] - m.m[0][1] * dets2x2[1]
		+ m.m[0][2] * dets2x2[0];
	dets3x3[1] = m.m[0][0] * dets2x2[3] - m.m[0][1] * dets2x2[2]
		+ m.m[0][3] * dets2x2[0];
	dets3x3[2] = m.m[0][0] * dets2x2[4] - m.m[0][2] * dets2x2[2]
		+ m.m[0][3] * dets2x2[1];
	dets3x3[3] = m.m[0][1] * dets2x2[4] - m.m[0][2] * dets2x2[3]
		+ m.m[0][3] * dets2x2[5];
	dets3x3[4] = m.m[0][0] * dets2x2[9] - m.m[0][1] * dets2x2[7]
		+ m.m[0][2] * dets2x2[6];
	dets3x3[5] = m.m[0][0] * dets2x2[10] - m.m[0][1] * dets2x2[8]
		+ m.m[0][3] * dets2x2[6];
	dets3x3[6] = m.m[0][0] * dets2x2[11] - m.m[0][2] * dets2x2[8]
		+ m.m[0][3] * dets2x2[7];
	dets3x3[7] = m.m[0][1] * dets2x2[11] - m.m[0][2] * dets2x2[10]
		+ m.m[0][3] * dets2x2[9];
	dets3x3_cont(m, dets3x3, dets2x2);
}

static void	ft_mtrx_get_dets2x2(const t_matrix m, double *dets2x2)
{
	dets2x2[0] = m.m[1][0] * m.m[2][1] - m.m[1][1] * m.m[2][0];
	dets2x2[1] = m.m[1][0] * m.m[2][2] - m.m[1][2] * m.m[2][0];
	dets2x2[2] = m.m[1][0] * m.m[2][3] - m.m[1][3] * m.m[2][0];
	dets2x2[3] = m.m[1][1] * m.m[2][3] - m.m[1][3] * m.m[2][1];
	dets2x2[4] = m.m[1][2] * m.m[2][3] - m.m[1][3] * m.m[2][2];
	dets2x2[5] = m.m[1][1] * m.m[2][2] - m.m[1][2] * m.m[2][1];
	dets2x2[6] = m.m[1][0] * m.m[3][1] - m.m[1][1] * m.m[3][0];
	dets2x2[7] = m.m[1][0] * m.m[3][2] - m.m[1][2] * m.m[3][0];
	dets2x2[8] = m.m[1][0] * m.m[3][3] - m.m[1][3] * m.m[3][0];
	dets2x2[9] = m.m[1][1] * m.m[3][2] - m.m[1][2] * m.m[3][1];
	dets2x2[10] = m.m[1][1] * m.m[3][3] - m.m[1][3] * m.m[3][1];
	dets2x2[11] = m.m[1][2] * m.m[3][3] - m.m[1][3] * m.m[3][2];
	dets2x2[12] = m.m[2][0] * m.m[3][1] - m.m[2][1] * m.m[3][0];
	dets2x2[13] = m.m[2][0] * m.m[3][2] - m.m[2][2] * m.m[3][0];
	dets2x2[14] = m.m[2][0] * m.m[3][3] - m.m[2][3] * m.m[3][0];
	dets2x2[15] = m.m[2][1] * m.m[3][2] - m.m[2][2] * m.m[3][1];
	dets2x2[16] = m.m[2][1] * m.m[3][3] - m.m[2][3] * m.m[3][1];
	dets2x2[17] = m.m[2][2] * m.m[3][3] - m.m[2][3] * m.m[3][2];
}

static t_matrix	ft_mtrx_make_inverse(const double *dets3x3,
	const double one_over_det)
{
	t_matrix	res;

	res.m[0][0] = dets3x3[15] * one_over_det;
	res.m[0][1] = dets3x3[11] * -one_over_det;
	res.m[0][2] = dets3x3[7] * one_over_det;
	res.m[0][3] = dets3x3[3] * -one_over_det;
	res.m[1][0] = dets3x3[14] * -one_over_det;
	res.m[1][1] = dets3x3[10] * one_over_det;
	res.m[1][2] = dets3x3[6] * -one_over_det;
	res.m[1][3] = dets3x3[2] * one_over_det;
	res.m[2][0] = dets3x3[13] * one_over_det;
	res.m[2][1] = dets3x3[9] * -one_over_det;
	res.m[2][2] = dets3x3[5] * one_over_det;
	res.m[2][3] = dets3x3[1] * -one_over_det;
	res.m[3][0] = dets3x3[12] * -one_over_det;
	res.m[3][1] = dets3x3[8] * one_over_det;
	res.m[3][2] = dets3x3[4] * -one_over_det;
	res.m[3][3] = dets3x3[0] * one_over_det;
	return (res);
}

t_matrix	ft_mtrx_inverse(const t_matrix m)
{
	double		dets2x2[18];
	double		dets3x3[16];
	double		det4x4;
	double		one_over_det;

	ft_mtrx_get_dets2x2(m, dets2x2);
	ft_mtrx_get_dets3x3(m, dets3x3, dets2x2);
	det4x4 = m.m[0][0] * dets3x3[15] - m.m[0][1] * dets3x3[14]
		+ m.m[0][2] * dets3x3[13] - m.m[0][3] * dets3x3[12];
	one_over_det = 1.0 / det4x4;
	return (ft_mtrx_make_inverse(dets3x3, one_over_det));
}
