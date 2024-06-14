/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_parse.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgosselk <lgosselk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/19 15:20:25 by lgosselk          #+#    #+#             */
/*   Updated: 2024/06/14 11:08:13 by lgosselk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static void	*create_object(t_base *base, char **args, int type)
{
	if (type == SPHERE)
		return (create_sphere(base, args));
	if (type == PLANE)
		return (create_plane(base, args));
	if (type == CYLINDER)
		return (create_cylinder(base, args));
	if (type == CONE)
		return (create_cone(base, args));
	return (NULL);
}

static bool	add_token(t_base *base, int type, char **args)
{
	t_objects	*new_object;

	new_object = (t_objects *)ft_malloc(sizeof(t_objects), &base->alloc);
	if (!new_object)
		return (false);
	new_object->next = NULL;
	new_object->type = type;
	new_object->object = create_object(base, args, type);
	if (new_object->object == NULL)
		return (print_error("Error\n", CREATE_ERR, 0));
	if (type == SPHERE)
		new_object->ft_hit = ft_sphere_hit;
	else if (type == PLANE)
		new_object->ft_hit = ft_plane_hit;
	else if (type == CYLINDER)
		new_object->ft_hit = ft_cylinder_hit;
	else if (type == CONE)
		new_object->ft_hit = ft_cone_hit;
	ft_object_add(&base->first_object, new_object);
	return (true);
}

static int	check_create_unique(t_base *base, char **args, int type)
{
	if (type == ALIGHT && base->alight == NULL)
	{
		base->alight = create_amblight(base, args);
		if (base->alight == NULL)
			return (print_error("Error\n", CREATE_ERR, 1));
		return (0);
	}
	if (type == CAMERA && base->camera == NULL)
	{
		base->camera = create_camera(base, args);
		if (!base->camera)
			return (print_error("Error\n", CREATE_ERR, 1));
		return (0);
	}
	if (type == LIGHT)
	{
		if (!add_light(base, args))
			return (print_error("Error\n", CREATE_ERR, 1));
		return (0);
	}
	return (print_error("Error\n", TWICE_ERR, 1));
}

static int	line_parse(t_base *base, char *line)
{
	int		type;
	char	**args;

	if (!line || *line == '\0' || *line == '#')
		return (0);
	if (!line_regex(line))
		return (print_error("Error\n", REGEX_ERR, 1));
	args = ft_split_alloc(line, ' ', &base->alloc);
	if (!args)
		return (print_error("Error\n", MALLOC_ERR, 1));
	type = extract_type(args[0]);
	if (type == -1)
		return (print_error("Error\n", OBJNAME_ERR, 1));
	if (!right_args(args, type))
		return (print_error("Error\n", ARGS_ERR, 1));
	if ((type == ALIGHT || type == CAMERA || type == LIGHT))
	{
		if (check_create_unique(base, args + 1, type) == 1)
			return (1);
	}
	else if (!add_token(base, type, args + 1))
		return (1);
	return (0);
}

int	file_parse(t_base *base, char *filepath)
{
	char	*line;
	int		infile;

	infile = open(filepath, O_RDONLY);
	if (infile < 0)
		return (perror(filepath), set_exit_code(base, 127, 1));
	line = get_next_line(infile);
	while (line != NULL)
	{
		if (line_parse(base, line) != 0)
		{
			free(line);
			close(infile);
			return (set_exit_code(base, 1, 1));
		}
		free(line);
		line = get_next_line(infile);
	}
	close(infile);
	if (!default_uniques(base))
		return (set_exit_code(base, 1, 1));
	return (EXIT_SUCCESS);
}
