/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: honlee <honlee@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/06 19:03:33 by honlee            #+#    #+#             */
/*   Updated: 2021/01/14 03:42:13 by honlee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_rt.h"

t_color				do_loop(t_map_info *map, double u, double v, size_t hit_idx)
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
	return (color_init(0.7, 0.7, 0.7));
}

int					start_world(t_map_info *map, int i, int j)
{
	t_wins		wins;
	t_data		img;

	wins.mlx = mlx_init();
	mlx_get_screen_size(wins.mlx, &map->screen_x, &map->screen_y);
	if (map->image_width > map->screen_x)
		map->image_width = map->screen_x;
	if (map->image_height > map->screen_y)
		map->image_height = map->screen_y;
	make_map_from_cam(map, 0);
	wins.win = mlx_new_window(wins.mlx, map->image_width,
					map->image_height, "miniRT");
	wins.img = &img;
	wins.map = map;
	img.img = mlx_new_image(wins.mlx, map->image_width, map->image_height);
	img.addr = mlx_get_data_addr(img.img, &img.bits_per_pixel,
					&img.line_length, &img.endian);
	draw_image(&wins, i, j);
	mlx_hook(wins.win, 2, 1L << 0, &key_press, &wins);
	mlx_hook(wins.win, 33, 1L << 17, &mouse_exit, &wins);
	mlx_loop(wins.mlx);
	return (1);
}

int					start_make_bmp(t_map_info *map, int j, int i, t_color pc)
{
	int			fd;
	t_rgbt		rgbt;
	int			zero;

	zero = 0;
	fd = open("miniRT.bmp", O_WRONLY | O_CREAT, 0644);
	if (fd == -1)
		return (ft_puterror(1));
	bmp_set_header(map, fd);
	while (++j < map->image_height)
	{
		i = -1;
		while (++i < map->image_width)
		{
			pc = do_loop(map, (double)i / (double)map->image_width,
						(double)j / (double)map->image_height, 0);
			rgbt = bmp_get_rgbt_by_color(pc);
			write(fd, &rgbt, 3);
		}
		i = -1;
		while (++i < (4 - (map->image_width * 3) % 4) % 4)
			write(fd, &zero, 1);
	}
	bmp_close_and_free(map, fd);
	return (1);
}

int					map_checker(t_map_info *map, int opt)
{
	if (map->r_cnt != 1 || map->c_cnt <= 0 || map->a_cnt != 1)
		return (ft_puterror(1));
	if (opt == 0)
		return (start_world(map, -1, -1));
	make_map_from_cam(map, 0);
	return (start_make_bmp(map, -1, -1, color_init(1, 1, 1)));
}

int					main(int ac, char **av)
{
	t_map_info			map;

	map_init(&map);
	if (rt_checker(av[1]) == -1)
		return (ft_puterror(1));
	if (ac == 2)
	{
		if (parse_make_map(&map, av[1]) == -1)
			return (ft_puterror(1));
		else
			return (map_checker(&map, 0));
	}
	else if (ac == 3 && av[2][0] == '-' && av[2][1] == '-' && av[2][2] == 's'
					&& av[2][3] == 'a' && av[2][4] == 'v' && av[2][5] == 'e'
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
