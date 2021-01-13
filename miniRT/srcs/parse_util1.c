/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_util1.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: honlee <honlee@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/06 19:21:36 by honlee            #+#    #+#             */
/*   Updated: 2021/01/12 23:29:44 by honlee           ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

int				parse_what_type(char **splited, size_t *nl, size_t *no)
{
	if (splited[0][0] == 'l')
		(*nl)++;
	else if (splited[0][0] == 's' && splited[0][1] == 'p')
		(*no)++;
	else if (splited[0][0] == 'p' && splited[0][1] == 'l')
		(*no)++;
	else if (splited[0][0] == 's' && splited[0][1] == 'q')
		(*no)++;
	else if (splited[0][0] == 'c' && splited[0][1] == 'y')
		(*no) = (*no) + 3;
	else if (splited[0][0] == 't' && splited[0][1] == 'r')
		(*no)++;
	return (0);
}

int				parse_get_num(int fd, size_t *num_lights, size_t *num_objs)
{
	char		*line;
	char		**splited;
	int			ret;

	while (1)
	{
		ret = get_next_line(fd, &line);
		if (!(line))
			return (-1);
		splited = ft_split(line, " \t\v\f\r");
		free(line);
		if (splited[0] != 0)
			parse_what_type(splited, num_lights, num_objs);
		ft_split_free(splited, parse_spl_len(splited));
		if (ret == 0)
			break;
	}
	return (0);
}

int				parse_map(t_map_info *map, int fd)
{
	char		*line;
	char		**splited;
	int			ret;
	int			parser_ret;

	while (1)
	{
		ret = get_next_line(fd, &line);
		if (!(line))
			return (-1);
		splited = ft_split(line, " \t\v\f\r");
		free(line);
		if (splited[0] != 0)
			parser_ret = parse_mapper(map, splited);
		ft_split_free(splited, parse_spl_len(splited));
		if (parser_ret == -1)
			return (-1);
		if (ret == 0)
			break;
	}
	return (0);
}

int				parse_make_map(t_map_info *map, const char *path)
{
	int				fd;

	map->objs_num = 0;
	map->lights_num = 0;
	map->o_iter = 0;
	map->l_iter = 0;
	if ((fd = open(path, O_RDONLY)) == -1)
		return (-1);
	if (parse_get_num(fd, &map->lights_num, &map->objs_num) == -1)
		return (ft_close(fd, -1));
	close(fd);
	if (!(map->lights = malloc(sizeof(t_light *) * map->lights_num)))
		return (-1);
	if (!(map->objs = malloc(sizeof(t_obj *) * map->objs_num)))
		return (-1);
	if ((fd = open(path, O_RDONLY)) == -1)
		return (-1);
	if (parse_map(map, fd) == -1)
		return (ft_close(fd, -1));
	close(fd);
	return (0);
}