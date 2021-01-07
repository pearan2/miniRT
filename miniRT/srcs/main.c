/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: honlee <honlee@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/06 19:03:33 by honlee            #+#    #+#             */
/*   Updated: 2021/01/07 04:43:04 by honlee           ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

void				start_world(t_map_info *map)
{
	printf("world start!!\n");
	map_free(map);
}

void				start_make_bmp(t_map_info *map)
{
	map = 0;
	printf("make_bmp start!!\n");
}

int					map_checker(t_map_info *map, int opt)
{
	t_vec fc;
	t_vec cx;
	double t;
	double theta;

	theta = map->fov_horizontal / 2;
	if (map->r_cnt != 1 || map->c_cnt != 1 || map->a_cnt)
		return (ft_puterror(1));
	map->apsect_ratio = (double)map->image_width / (double)map->image_height;
	map->orient = vec_to_unit(map->orient);
	map->viewport_height = 2.0;
	map->viewport_width = map->apsect_ratio * map->viewport_height;
	t = sqrt(map->apsect_ratio / tan(ft_to_radian(theta)));
	map->focal_length = pow(t, 2);
	fc = vec_plus(map->origin, vec_scala_multi(map->orient, t));
	cx = vec_plus(vec_scala_multi(map->orient, t * tan(ft_to_radian(theta))), fc);
	theta = ft_to_degree(atan(1 / map->focal_length));
	cx = vec_plus(vec_scala_multi(map->orient, t * tan(ft_to_radian(theta))), fc);
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