/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleaning.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbelomet <sbelomet@42lausanne.ch>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/22 10:07:41 by lgosselk          #+#    #+#             */
/*   Updated: 2024/05/28 13:00:59 by sbelomet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	on_destroy(t_base *base)
{
	if (base->win_ptr)
		mlx_destroy_window(base->mlx_ptr, base->win_ptr);
	if (base->mlx_ptr)
		free(base->mlx_ptr);
	ft_malloc_clear(&base->alloc);
	exit(base->exit_code);
}

int	close_window(t_base *base)
{
	on_destroy(base);
	return (0);
}
