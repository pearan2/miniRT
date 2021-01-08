/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: honlee <honlee@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/06 19:03:33 by honlee            #+#    #+#             */
/*   Updated: 2021/01/08 02:18:36 by honlee           ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

int					start_world(t_map_info *map)
{
	printf("world start!!\n");
	map_free(map);
	return (1);
}

int					start_make_bmp(t_map_info *map)
{
	map = 0;
	printf("make_bmp start!!\n");
	return (1);
}

int					map_checker(t_map_info *map, int opt)
{
	double theta;

	theta = map->fov_horizontal / 2;
	if (map->r_cnt != 1 || map->c_cnt != 1 || map->a_cnt != 1)
		return (ft_puterror(1));
	map->aspect_ratio = (double)map->image_width / (double)map->image_height;
	map->orient = vec_to_unit(map->orient);
	map->viewport_height = 2.0;
	map->viewport_width = map->aspect_ratio * map->viewport_height;
	map->focal_length = map->aspect_ratio / tan(ft_to_radian(theta));
	map->p_c = vec_init(0, 0, map->focal_length);
	map->p_ll = vec_init(-map->viewport_width / 2, -map->viewport_height / 2, map->focal_length);
	map->p_hl = vec_init(-map->viewport_width / 2, map->viewport_height / 2, map->focal_length);
	map->p_lr = vec_init(map->viewport_width / 2, -map->viewport_height / 2, map->focal_length);
	make_view_plane(map);
	if (opt == 0)
		return (start_world(map));
	return (start_make_bmp(map));
}

int					main(int ac, char **av)
{
	t_map_info			map;

	map.r_cnt = 0;
	map.c_cnt = 0;
	map.a_cnt = 0;
	if (ac == 2)
	{
		if (parse_make_map(&map, av[1]) == -1)
			return (ft_puterror(1));
		else
			return (map_checker(&map, 0));
	}
	else if (ac == 3 && av[2][0] == '-' && av[2][1] == '-'
					&& av[2][2] == 's' && av[2][3] == 'a'
					&& av[2][4] == 'v' && av[2][5] == 'e'
					&& av[2][6] == 0)
	{
		if (parse_make_map(&map, av[1]) == -1)
			return (ft_puterror(1));
		else
			return (map_checker(&map, 1));
	}
	else
		return (ft_puterror(0));
	return (0);
}