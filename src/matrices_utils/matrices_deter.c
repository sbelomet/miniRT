/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrices_deter.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbelomet <sbelomet@42lausanne.ch>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/16 15:15:11 by sbelomet          #+#    #+#             */
/*   Updated: 2024/05/28 13:00:59 by sbelomet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	ft_mtrx_cofactor(t_matrix *m, t_matrix *tmp_m,
	const int q, const int size)
{
	int	index[2];
	int	row;
	int	col;

	index[0] = 0;
	index[1] = 0;
	row = 0;
	while (row < size)
	{
		col = 0;
		while (col < size)
		{
			if (row != 0 && col != q)
			{
				tmp_m->m[index[0]][index[1]++] = m->m[row][col];
				if (index[1] == size - 1)
				{
					index[1] = 0;
					index[0]++;
				}
			}
			col++;
		}
		row++;
	}
}

double	ft_mtrx_det(t_matrix *m, int size)
{
	double		det;
	t_matrix	tmp_m;
	int			sign;
	int			i;

	if (size == 1)
		return (m->m[0][0]);
	det = 0;
	tmp_m = ft_mtrx_new();
	sign = 1;
	i = 0;
	while (i < size)
	{
		ft_mtrx_cofactor(m, &tmp_m, i, size);
		det += sign * m->m[0][i] * ft_mtrx_det(&tmp_m, size - 1);
		sign = -sign;
		i++;
	}
	return (det);
}
