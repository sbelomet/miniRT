/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils3.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgosselk <lgosselk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/11 13:50:46 by lgosselk          #+#    #+#             */
/*   Updated: 2024/06/11 15:33:53 by lgosselk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static bool	check_exist(t_base *base, const char *arg)
{
	int			i;
	char		**array;

	i = -1;
	array = ft_split_alloc(arg, ',', &base->alloc);
	if (!array)
		return (false);
	if (array[0] && array[1] && array[2] && !array[3])
		return (true);
	return (false);
}

bool	the_fucking_args_works(t_base *base, char **args, const int type)
{
	if (type == CAMERA && (check_exist(base, args[0])
			&& check_exist(base, args[1])))
		return (true);
	if (type == ALIGHT && check_exist(base, args[1]))
		return (true);
	if (type == LIGHT && (check_exist(base, args[0])
			&& check_exist(base, args[2])))
		return (true);
	if (type == PLANE && (check_exist(base, args[0])
			&& check_exist(base, args[1]) && check_exist(base, args[2])))
		return (true);
	if (type == SPHERE && (check_exist(base, args[0])
			&& check_exist(base, args[2])))
		return (true);
	if (type == CYLINDER && (check_exist(base, args[0])
			&& check_exist(base, args[1]) && check_exist(base, args[4])))
		return (true);
	if (type == CONE && (check_exist(base, args[0])
			&& check_exist(base, args[1]) && check_exist(base, args[4])))
		return (true);
	return (false);
}
