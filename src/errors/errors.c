/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgosselk <lgosselk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/14 10:45:52 by lgosselk          #+#    #+#             */
/*   Updated: 2024/04/24 15:15:21 by lgosselk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int	print_error(char *error, char *var, int return_val)
{
	if (error)
	{
		while (*error)
			write(2, error++, 1);
		if (var)
		{
			while (*var)
				write(2, var++, 1);
		}
		write(2, "\n", 1);
	}
	return (return_val);
}

void	*print_error_null(char *error, char *var)
{
	if (error)
	{
		while (*error)
			write(2, error++, 1);
		if (var)
		{
			while (*var)
				write(2, var++, 1);
		}
		write(2, "\n", 1);
	}
	return (NULL);
}

int	set_exit_code(t_base *base, int exit_code, int return_val)
{
	base->exit_code = exit_code;
	return (return_val);
}
