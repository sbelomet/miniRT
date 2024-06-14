/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgosselk <lgosselk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/26 10:34:31 by lgosselk          #+#    #+#             */
/*   Updated: 2024/06/14 11:21:11 by lgosselk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

bool	line_regex(char *line)
{
	while (*line)
	{
		if (*line == '\n')
			return (true);
		if (((*line == '-') || (*line == '+'))
			&& (*(line + 1) == '-' || *(line + 1) == '+'))
			return (false);
		if (ft_isalnum(*line) && (*(line + 1) == '-' || *(line + 1) == '+'))
			return (false);
		if (!ft_isalnum(*line) && !(*line == '.') && !(*line == ' ')
			&& !(*line == ',') && !(*line == '-') && !(*line == '+'))
			return (false);
		line++;
	}
	return (true);
}

int	extract_type(char *arg)
{
	if (arg)
	{
		if (ft_equal_strs("A", arg))
			return (ALIGHT);
		if (ft_equal_strs("C", arg))
			return (CAMERA);
		if (ft_equal_strs("L", arg))
			return (LIGHT);
		if (ft_equal_strs("pl", arg))
			return (PLANE);
		if (ft_equal_strs("sp", arg))
			return (SPHERE);
		if (ft_equal_strs("cy", arg))
			return (CYLINDER);
		if (ft_equal_strs("co", arg))
			return (CONE);
	}
	return (-1);
}

bool	only_numbers(char *arg)
{
	while (*arg)
	{
		if (!ft_isdigit(*arg) && !(*arg == '.') && !(*arg == ',')
			&& !(*arg == '-') && !(*arg == '+'))
			return (false);
		arg++;
	}
	return (true);
}

bool	right_args(char **args, int type)
{
	int	i;

	i = -1;
	while (args[++i])
	{
		if (i > 0)
		{
			if (!only_numbers(args[i]))
				return (false);
		}	
	}
	if (type == ALIGHT && i != 3)
		return (false);
	if ((type == CAMERA || type == LIGHT || type == PLANE || type == SPHERE)
		&& i != 4)
		return (false);
	if ((type == CYLINDER || type == CONE) && i != 6)
		return (false);
	return (true);
}

t_objects	*get_last_object(t_objects *list)
{
	t_objects	*temp;

	if (!list)
		return (list);
	while (list)
	{
		temp = list;
		list = list->next;
	}
	return (temp);
}
