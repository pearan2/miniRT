/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   event_util1.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: honlee <honlee@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/10 22:48:10 by honlee            #+#    #+#             */
/*   Updated: 2021/01/11 19:26:20 by honlee           ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

int					key_press(int keycode, t_wins *wins)
{
	keycode = 0;
	mlx_clear_window(wins->mlx, wins->win);
	wins->map->origin = vec_plus(wins->map->origin, vec_scala_multi(wins->map->orient, 0.05));
	wins->map->p_ll = vec_plus(wins->map->p_ll, vec_scala_multi(wins->map->orient, 0.05));
	wins->map->p_lr = vec_plus(wins->map->p_lr, vec_scala_multi(wins->map->orient, 0.05));
	wins->map->p_hl = vec_plus(wins->map->p_hl, vec_scala_multi(wins->map->orient, 0.05));
	wins->map->vertical = vec_minus(wins->map->p_hl, wins->map->p_ll);
	wins->map->horizontal = vec_minus(wins->map->p_lr, wins->map->p_ll);	
	printf("origin >> %f,%f,%f\n", wins->map->origin.x, wins->map->origin.y, wins->map->origin.z);
	draw_image(wins, -1, -1);
	return (0);
}

int					mouse_exit(t_wins *wins)
{
	mlx_clear_window(wins->mlx, wins->win);
	mlx_destroy_window(wins->mlx, wins->win);
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
			pixel_color = do_loop(wins->map, (double)i / (double)wins->map->image_width
						,(double)j / (double)wins->map->image_height, 0);
			ft_mlx_pixel_put(wins->img, i, wins->map->image_height - j, pixel_color);
		}
	}
	mlx_put_image_to_window(wins->mlx, wins->win, wins->img->img, 0, 0);
}