/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_parse.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbelomet <sbelomet@42lausanne.ch>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/19 15:20:25 by lgosselk          #+#    #+#             */
/*   Updated: 2024/04/23 11:57:48 by sbelomet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"


static bool line_regex(char *line)
{
	while (*line)
	{
		if (ft_isalnum(*line) == 1 || !(*line == '.') || !(*line == ' ')
			|| !(*line == ',') || !(*line == '-'))
			return (false);
	}
	return (true);
}

static char	*extract_id(char *line)
{
	int	i;

	i = 0;
	while (line[i] != ' ')
		i++;
	if (ft_equal_strs("A", line[i]) == 1)
		return (ALIGHT);
	if (ft_equal_strs("C", line[i]) == 1)
		return (CAMERA);
	if (ft_equal_strs("L", line[i]) == 1)
		return (LIGHT);
	if (ft_equal_strs("p", line[i]) == 1
		&& ft_equal_strs("l", line[i + 1]) == 1)
		return (PLANE);
	if (ft_equal_strs("s", line[i]) == 1
		&& ft_equal_strs("p", line[i + 1]) == 1)
		return (SPHERE);
	if (ft_equal_strs("c", line[i]) == 1
		&& ft_equal_strs("y", line[i + 1]) == 1)
		return (CYLINDER);
	return (-1);
}

static bool	already_listed(t_base *base, int id)
{
	t_token	*list;

	list = base->first_token;
	while (list)
	{
		if ((ft_equal_strs(list->id, id) == 1)
			&& id == ALIGHT || id == CAMERA || id == LIGHT)
			return (true);
	}
	return (false);
}

static t_token	*get_last_token(t_token *list)
{
	t_token	*temp;

	if (!list)
		return (list);
	while (list)
	{
		temp = list;
		list = list->next;
	}
	return (temp);
}

static t_alight *create_amblight(char *line)
{
	int	i;
	t_alight *amblight;

	amblight = (t_alight *) malloc(sizeof(t_alight));
	if (!amblight)
		return (NULL);
	while (ft_isdigit(*line) == 1)
		line++;
	amblight->ratio = parse_ratio(line);
	
}

static void	*create_object(char *line, int id)
{
	if (id == ALIGHT)
		return (create_amblight(line));
	if (id == CAMERA)
		return (create_camera(line));
	if (id == LIGHT)
		return (create_light(line));
	if (id == SPHERE)
		return (create_sphere(line));
	if (id == PLANE)
		return (create_plane(line));
	if (id == CYLINDER)
		return (create_cylinder(line));
}

static bool	add_token(t_base *base, int id, char *line)
{
	t_token	*new_token;
	t_token	*last_token;
	
	new_token = (t_token *) malloc(sizeof(t_token));
	if (!new_token)
		return (false);
	new_token->next = NULL;
	new_token->id = id;
	new_token->object = create_object(line, id); // Peut retourner NULL, a gerer.
	if (base->first_token == NULL)
		base->first_token = new_token;
	else
	{
		last_token = get_last_token(base->first_token);
		last_token->next = new_token;
	}
	return (true);
}

static int	line_parse(t_base *base, char *line)
{
	int	id;
	if (line)
	{
		if (!line_regex(line))
		return (print_error("Error\n", REGEX_ERR, 1));
		id = extract_type(line);
		if (id == -1)
			return (print_error("Error\n", OBJNAME_ERR, 1));
		if (already_listed(base, id))
			return (print_error("Error\n", TWICE_ERR, 1));
		if (!add_token(base, id, line))
		{}	// error return;
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
