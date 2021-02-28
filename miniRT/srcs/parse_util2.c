/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_util2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: honlee <honlee@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/06 22:36:21 by honlee            #+#    #+#             */
/*   Updated: 2021/01/13 20:15:15 by honlee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_rt.h"

size_t			parse_spl_len(char **splited)
{
	size_t		ret;

	ret = 0;
	while (splited[ret] != 0)
		ret++;
	return (ret);
}

int				parse_resol(t_map_info *map, char **splited)
{
	if (parse_spl_len(splited) != 3)
		return (-1);
	map->image_width = ft_atoi(splited[1]);
	map->image_height = ft_atoi(splited[2]);
	if (map->image_height <= 0)
		return (-1);
	if (map->image_width <= 0)
		return (-1);
	map->r_cnt++;
	return (0);
}

int				parse_amb(t_map_info *map, char **splited)
{
	if (parse_spl_len(splited) != 3)
		return (-1);
	map->ambient.ratio = ft_atod(splited[1]);
	if (map->ambient.ratio < 0.0 || map->ambient.ratio > 1.0)
		return (-1);
	if ((parse_color(ft_split(splited[2], ","), &map->ambient.color)) == -1)
		return (-1);
	map->a_cnt++;
	return (0);
}

int				parse_mapper(t_map_info *map, char **splited)
{
	if (splited[0][0] == 'R')
		return (parse_resol(map, splited));
	else if (splited[0][0] == 'A')
		return (parse_amb(map, splited));
	else if (splited[0][0] == 'c' && splited[0][1] == 'y')
		return (parse_cylinder(map, splited));
	else if (splited[0][0] == 'c')
		return (parse_cam(map, splited));
	else if (splited[0][0] == 'l')
		return (parse_light(map, splited));
	else if (splited[0][0] == 's' && splited[0][1] == 'p')
		return (parse_sphere(map, splited));
	else if (splited[0][0] == 'p' && splited[0][1] == 'l')
		return (parse_plane(map, splited));
	else if (splited[0][0] == 's' && splited[0][1] == 'q')
		return (parse_square(map, splited));
	else if (splited[0][0] == 't' && splited[0][1] == 'r')
		return (parse_tri(map, splited));
	return (-1);
}
