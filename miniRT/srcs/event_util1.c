/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   event_util1.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: honlee <honlee@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/10 22:48:10 by honlee            #+#    #+#             */
/*   Updated: 2021/01/13 05:06:23 by honlee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_rt.h"

int					key_press(int keycode, t_wins *wins)
{
	if (keycode == 65361 || keycode == 65363)
	{
		if (keycode == 65361)
			wins->map->n_c_idx--;
		if (keycode == 65363)
			wins->map->n_c_idx++;
		if (wins->map->n_c_idx < 0)
			wins->map->n_c_idx = wins->map->c_cnt - 1;
		if (wins->map->n_c_idx >= (int)wins->map->c_cnt)
			wins->map->n_c_idx = 0;
		mlx_clear_window(wins->mlx, wins->win);
		make_map_from_cam(wins->map, wins->map->n_c_idx);
		draw_image(wins, -1, -1);
	}
	else if (keycode == 65307)
	{
		mlx_clear_window(wins->mlx, wins->win);
		mlx_destroy_window(wins->mlx, wins->win);
		map_free(wins->map);
		exit(0);
	}
	return (0);
}

int					mouse_exit(t_wins *wins)
{
	mlx_clear_window(wins->mlx, wins->win);
	mlx_destroy_window(wins->mlx, wins->win);
	map_free(wins->map);
	exit(0);
	return (0);
}

void				draw_image(t_wins *wins, int i, int j)
{
	t_color			pixel_color;

	while (++j < wins->map->image_height)
	{
		i = -1;
		while (++i < wins->map->image_width)
		{
			pixel_color = do_loop(wins->map, (double)i /
						(double)wins->map->image_width,
						(double)j / (double)wins->map->image_height, 0);
			ft_mlx_pixel_put(wins->img, i,
								wins->map->image_height - j, pixel_color);
		}
	}
	mlx_put_image_to_window(wins->mlx, wins->win, wins->img->img, 0, 0);
}
