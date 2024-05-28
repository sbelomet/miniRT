/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrices.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbelomet <sbelomet@42lausanne.ch>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/14 11:33:44 by sbelomet          #+#    #+#             */
/*   Updated: 2024/05/28 13:00:59 by sbelomet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_matrix	ft_mtrx_new(void)
{
	t_matrix	m;
	int			i;
	int			j;

	i = 0;
	while (i < 4)
	{
		j = 0;
		while (j < 4)
		{
			if (i == j)
				m.m[i][j] = 1;
			else
				m.m[i][j] = 0;
			j++;
		}
		i++;
	}
	return (m);
}
/* 
t_matrix	ft_mtrx_new2(const t_vector4 x, const t_vector4 y,
	const t_vector4 z, const t_vector4 w)
{
	t_matrix	m;

	m.c1 = x;
	m.c2 = y;
	m.c3 = z;
	m.c4 = w;
	return (m);
} */

void	ft_mtrx_print(const t_matrix m, const char *name)
{
	printf("Matrix %s:\n", name);
	printf("[%f][%f][%f][%f]\n", m.m[0][0], m.m[0][1], m.m[0][2], m.m[0][3]);
	printf("[%f][%f][%f][%f]\n", m.m[1][0], m.m[1][1], m.m[1][2], m.m[1][3]);
	printf("[%f][%f][%f][%f]\n", m.m[2][0], m.m[2][1], m.m[2][2], m.m[2][3]);
	printf("[%f][%f][%f][%f]\n", m.m[3][0], m.m[3][1], m.m[3][2], m.m[3][3]);
}
