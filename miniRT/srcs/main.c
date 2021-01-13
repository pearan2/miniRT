/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: honlee <honlee@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/06 19:03:33 by honlee            #+#    #+#             */
/*   Updated: 2021/01/13 05:08:32 by honlee           ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

t_color			do_loop(t_map_info *map, double u, double v, size_t hit_idx)
{
	t_vec		unit_dir;
	double		t;
	double		t_max;
	double		(*fp)(void *, t_vec, t_vec);
	size_t		idx;

	idx = 0;
	unit_dir = vec_plus(map->p_ll, vec_scala_multi(map->horizontal, u));
	unit_dir = vec_plus(unit_dir, vec_scala_multi(map->vertical, v));
	unit_dir = vec_to_unit(vec_minus(unit_dir, map->origin));
	t_max = DBL_MAX;
	while (idx < map->objs_num)
	{
		fp = hit_func_mapper(map, idx);
		t = fp(map->objs[idx]->data, map->origin, unit_dir);
		if (t != -1.0 && t < t_max)
		{
			t_max = t;
			hit_idx = idx;
		}
		idx++;
	}
	if (t_max != DBL_MAX)
		return (get_hit_col(map, unit_dir, t_max, hit_idx));
	else
		return (color_init(0.7, 0.7, 0.7));	
}

int					start_world(t_map_info *map, int i, int j)
{
	t_wins		wins;
	t_data		img;

	wins.mlx = mlx_init();
	wins.win = mlx_new_window(wins.mlx, map->image_width, map->image_height, "miniRT");
	wins.img = &img;
	wins.map = map;
	img.img = mlx_new_image(wins.mlx, map->image_width, map->image_height);
	img.addr = mlx_get_data_addr(img.img, &img.bits_per_pixel, &img.line_length, &img.endian);
	draw_image(&wins, i, j);

	mlx_hook(wins.win, 2, 1L<<0, &key_press, &wins);
	//in linux
	mlx_hook(wins.win, 33, 1L<<17, &mouse_exit, &wins);
	//in mac
	//mlx_hook(wins.win, 17, 0, &mouse_exit, &wins);
	mlx_loop(wins.mlx);
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
	map->vertical = vec_minus(map->p_hl, map->p_ll);
	map->horizontal = vec_minus(map->p_lr, map->p_ll);	
	if (opt == 0)
		return (start_world(map, -1, -1));
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