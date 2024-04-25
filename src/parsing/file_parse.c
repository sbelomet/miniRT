/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_parse.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgosselk <lgosselk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/19 15:20:25 by lgosselk          #+#    #+#             */
/*   Updated: 2024/04/25 11:38:32 by lgosselk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static bool line_regex(char *line)
{
	while (*line)
	{
		if (*line == '\n')
			return (true);
		if (((*line == '-') || (*line == '+')) 
			&& (*(line + 1) == '-' || *(line + 1) == '+'))
			return (false);
		if (!ft_isalnum(*line) && !(*line == '.') && !(*line == ' ')
			&& !(*line == ',') && !(*line == '-') && !(*line == '+'))
			return (false);
		line++;
	}
	return (true);
}

static int	extract_type(char *arg)
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
	}
	return (-1);
}

static t_objects	*get_last_object(t_objects *list)
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

static double ft_atof(char *str)
{
	int		i;
	double	value;
	double	factor;

	i = 0;
	factor = 1;
	value = 0.0;
	if (str[i] == '-')
		factor = -1;
	if (str[i] == '-' || str[i] == '+')
		i++;
	while (str[i] >= '0' && str[i] <= '9')
	{
		value = value * 10 + (str[i] - '0');
		i++;
	}
	if (str[i] == '.')
		i++;
	while (str[i] >= '0' && str[i] <= '9')
	{
		value = value * 10 + (str[i] - '0');
		factor = factor / 10;
		i++;
	}
	return (factor * value);
}


static	bool	out_range(double min, double max, double value)
{
	if (value < min || value > max)
		return (true);
	return (false);
}

static	bool	out_range_color(t_color color)
{
	if ((color.red < 0 || color.red > 255)
		|| (color.green < 0 || color.green > 255)
		|| (color.blue < 0 || color.blue > 255)
		||(color.alpha < 0 || color.alpha > 1))
		return (true);
	return (false);
}

static	bool	out_range_norm(t_vector3 vector)
{
	if ((vector.x < -1 || vector.x > 1) || (vector.y < -1 || vector.y > 1)
		|| (vector.z < -1 || vector.z > 1))
		return (true);
	return (false);
}

static t_color	parse_color(char *arg)
{
	int		i;
	t_color	color;
	char	**colors;

	colors = ft_split(arg, ',');
	if (!colors)
		return (ft_color_new(0,0,0,0));
	color.red = ft_atof(colors[0]);
	color.green = ft_atof(colors[1]);
	color.blue = ft_atof(colors[2]);
	color.alpha = (double)0.0;
	i = -1;
	while (colors[++i])
		free(colors[i]);
	free(colors);
	return (color);
}

static t_vector3	parse_vector(char *arg)
{
	int			i;
	t_vector3	vector;
	char		**vectors;

	vectors = ft_split(arg, ',');
	if (!vectors)
		return (ft_vec3_new(0, 0, 0));
	vector.x = ft_atof(vectors[0]);
	vector.y = ft_atof(vectors[1]);
	vector.z = ft_atof(vectors[2]);
	i = -1;
	while (vectors[++i])
		free(vectors[i]);
	free(vectors);
	return (vector);
}

static t_light	*create_light(char **args)
{
	t_light		*light;

	light = (t_light *) malloc (sizeof(t_light));
	if (!light)
		return (print_error_null("Error\n", MALLOC_ERR));
	light->coord = parse_vector(args[0]);
	light->ratio = ft_atof(args[1]);
	if (out_range(0, 1, light->ratio))
		return (free(light), print_error_null("Error\n", RANGE_ERR));
	light->color = parse_color(args[2]);
	if (out_range_color(light->color))
		return (free(light), print_error_null("Error\n", RANGE_ERR));
	return (light);
}

static t_sphere	*create_sphere(char **args)
{
	t_sphere	*sphere;

	sphere = (t_sphere *) malloc (sizeof(t_sphere));
	if (!sphere)
		return (print_error_null("Error\n", MALLOC_ERR));
	sphere->center = parse_vector(args[0]);
	sphere->diam = ft_atof(args[1]);
	sphere->radius = sphere->diam / 2;
	sphere->color = parse_color(args[2]);
	if (out_range_color(sphere->color))
		return (free(sphere), print_error_null("Error\n", RANGE_ERR));
	return (sphere);
}

static t_plane	*create_plane(char **args)
{
	t_plane	*plane;

	plane = (t_plane *) malloc (sizeof(t_plane));
	if (!plane)
		return (print_error_null("Error\n", MALLOC_ERR));
	plane->coord = parse_vector(args[0]);
	plane->norm = parse_vector(args[1]);
	if (out_range_norm(plane->norm))
		return (free(plane), print_error_null("Error\n", RANGE_ERR));
	plane->color = parse_color(args[2]);
	if (out_range_color(plane->color))
		return (free(plane), print_error_null("Error\n", RANGE_ERR));
	return (plane);
}

static t_cylin	*create_cylinder(char **args)
{
	t_cylin	*cylinder;

	cylinder = (t_cylin *) malloc (sizeof(t_cylin));
	if (!cylinder)
		return (print_error_null("Error\n", MALLOC_ERR));
	cylinder->coord = parse_vector(args[0]);
	cylinder->ori = parse_vector(args[1]);
	if (out_range_norm(cylinder->ori))
		return (free(cylinder), print_error_null("Error\n", RANGE_ERR));
	cylinder->diam = ft_atof(args[2]);
	cylinder->height = ft_atof(args[3]);
	cylinder->color = parse_color(args[4]);
	if (out_range_color(cylinder->color))
		return (free(cylinder), print_error_null("Error\n", RANGE_ERR));
	return (cylinder);
}

static t_camera	*create_camera(char **args)
{
	t_camera	*camera;

	camera = (t_camera *) malloc (sizeof(t_camera));
	if (!camera)
		return (print_error_null("Error\n", MALLOC_ERR));
	camera->lookfrom = parse_vector(args[0]);
	camera->ori = parse_vector(args[1]);
	if (out_range_norm(camera->ori))
		return (free(camera), print_error_null("Error\n", RANGE_ERR));
	camera->vfov = ft_atoi(args[2]);
	if (camera->vfov < 0 || camera->vfov > 180)
		return (free(camera), print_error_null("Error\n", RANGE_ERR));
	return (camera);
}

static t_alight *create_amblight(char **args)
{
	t_alight	*amblight;

	amblight = (t_alight *) malloc(sizeof(t_alight));
	if (!amblight)
		return (print_error_null("Error\n", MALLOC_ERR));
	amblight->ratio = ft_atof(args[0]);
	if (out_range(0, 1, amblight->ratio))
		return (free(amblight), print_error_null("Error\n", RANGE_ERR));
	amblight->color = parse_color(args[1]);
	if (out_range_color(amblight->color))
		return (free(amblight), print_error_null("Error\n", RANGE_ERR));
	return (amblight);
}

static void	*create_object(char **args, int id)
{
	if (id == SPHERE)
		return (create_sphere(args));
	if (id == PLANE)
		return (create_plane(args));
	if (id == CYLINDER)
		return (create_cylinder(args));
	return (NULL);
}

static bool	add_token(t_base *base, int type, char **args)
{
	t_objects	*new_object;
	t_objects	*last_object;

	new_object = (t_objects *) malloc(sizeof(t_objects));
	if (!new_object)
		return (false);
	new_object->id = 0;
	new_object->next = NULL;
	new_object->type = type;
	new_object->object = create_object(args, type);
	if (new_object->type == CYLINDER)
	{
		t_cylin *cylinder = (t_cylin *)new_object->object;
		printf("x: %lf, y: %lf, z: %lf\n",
			cylinder->coord.x, cylinder->coord.y, cylinder->coord.z);
		printf("normx: %lf, normy: %lf, normz: %lf\n",
			cylinder->ori.x, cylinder->ori.y, cylinder->ori.z);
		printf("diam: %lf\n",
			cylinder->diam);
		printf("height: %lf\n",
			cylinder->height);
		printf("red: %lf, green: %lf, blue: %lf, alpha: %lf\n",
			cylinder->color.red, cylinder->color.green, cylinder->color.blue, cylinder->color.alpha);
	}
	if (new_object->object == NULL)
		return (free(new_object), false);
	if (base->first_object == NULL)
		base->first_object = new_object;
	else
	{
		last_object = get_last_object(base->first_object);
		new_object->id = last_object->id + 1;
		last_object->next = new_object;
	}
	return (true);
}

static int	check_create_unique(t_base *base, char **args, int type)
{
    if (type == ALIGHT)
	{
		base->uniques.alight = create_amblight(args);
		if (base->uniques.alight == NULL)
			return (print_error("Error\n", CREATE_ERR, 1));
		return (0);
	}
	if (type == CAMERA)
	{
		base->uniques.camera = create_camera(args);
		if (!base->uniques.camera)
			return (print_error("Error\n", CREATE_ERR, 1));
		return (0);
	}
	if (type == LIGHT)
	{
		base->uniques.light = create_light(args);
		if (!base->uniques.light)
			return (print_error("Error\n", CREATE_ERR, 1));
		return (0);
	}
	return (print_error("Error\n", TWICE_ERR, 1));
}

static int	line_parse(t_base *base, char *line)
{
	int		type;
	char	**args;
	
	if (line)
	{
		if (!line_regex(line))
			return (print_error("Error\n", REGEX_ERR, 1));
		args = ft_split(line, ' ');
		if (!args)
			return (print_error("Error\n", MALLOC_ERR, 1));
		type = extract_type(args[0]);
		if (type == -1)
			return (print_error("Error\n", OBJNAME_ERR, 1));
		if (type == ALIGHT || type == CAMERA || type == LIGHT)
		{
			if (check_create_unique(base, args + 1, type) == 1)
				return (1);
		}
		else if (!add_token(base, type, args + 1))
			return (print_error("Error\n", CREATE_ERR, 1));
	}
	return (0);
}

int	file_parse(t_base *base, char *filepath)
{
	char	*line;
	int		infile;

	infile = open(filepath, O_RDONLY);
	if (infile < 0)
		return (perror(filepath), set_exit_code(base, 1, 1));
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
	return (EXIT_SUCCESS);
}
