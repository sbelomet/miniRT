/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleaning.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbelomet <sbelomet@42lausanne.ch>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/22 10:07:41 by lgosselk          #+#    #+#             */
/*   Updated: 2024/05/30 15:01:03 by sbelomet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static void	ft_free_objects(t_objects *first_object)
{
	t_objects	*tmp1;
	t_objects	*tmp2;

	tmp1 = first_object;
	if (tmp1)
	{
		while (tmp1)
		{
			tmp2 = tmp1->next;
			free(tmp1->object);
			free(tmp1);
			tmp1 = tmp2;
		}
	}
}

static void	ft_free_lights(t_light *first_light)
{
	t_light	*tmp1;
	t_light	*tmp2;

	tmp1 = first_light;
	if (tmp1)
	{
		while (tmp1)
		{
			tmp2 = tmp1->next;
			free(tmp1);
			tmp1 = tmp2;
		}
	}
}

void	on_destroy(t_base *base)
{
	if (base->image.img_ptr)
		mlx_destroy_image(base->mlx_ptr, base->image.img_ptr);
	if (base->win_ptr)
		mlx_destroy_window(base->mlx_ptr, base->win_ptr);
	if (base->mlx_ptr)
		mlx_destroy(base->mlx_ptr);
	if (base->alight)
		free(base->alight);
	if (base->camera)
		free(base->camera);
	ft_malloc_clear(&base->alloc);
	ft_free_lights(base->first_light);
	ft_free_objects(base->first_object);
	exit(base->exit_code);
}

int	close_window(t_base *base)
{
	on_destroy(base);
	return (0);
}
