/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbelomet <sbelomet@42lausanne.ch>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/08 11:38:22 by sbelomet          #+#    #+#             */
/*   Updated: 2024/06/06 09:58:04 by sbelomet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static int	check_args(int argc, char **argv)
{
	char	*extension;

	if (argc != 2 || !argv[1])
		return (print_error(BAD_ARGS, NULL, 0));
	extension = ft_strrchr(argv[1], '.');
	if (!extension || !ft_equal_strs(extension, ".rt"))
		return (print_error(EXT_ERR, NULL, 0));
	return (1);
}

int	main(const int argc, char **argv)
{
	t_base		base;

	if (!check_args(argc, argv))
		return (EXIT_FAILURE);
	set_base(&base);
	if (file_parse(&base, argv[1]) == 1)
		on_destroy(&base);
	if (ft_base_init(&base) == 1)
		on_destroy(&base);
	ft_render(&base);
	ft_hooks(&base);
	on_destroy(&base);
	return (EXIT_SUCCESS);
}
