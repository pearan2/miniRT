/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rotate_util2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: honlee <honlee@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/23 19:04:03 by honlee            #+#    #+#             */
/*   Updated: 2021/02/24 00:38:38 by honlee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_rt.h"

void			make_map_from_cam(t_map_info *map, size_t c_idx)
{
	double theta;

	map->orient = map->cams[c_idx]->orient;
	map->origin = map->cams[c_idx]->origin;
	map->fov_horizontal = map->cams[c_idx]->fov_horizontal;
	theta = map->fov_horizontal / 2;
	map->aspect_ratio = (double)map->image_width / (double)map->image_height;
	map->orient = vec_to_unit(map->orient);
	map->viewport_height = 2.0;
	map->viewport_width = map->aspect_ratio * map->viewport_height;
	map->focal_length = map->aspect_ratio / tan(ft_to_radian(theta));
	map->p_c = vec_init(0, 0, map->focal_length);
	map->p_ll = vec_init(-map->viewport_width / 2,
				-map->viewport_height / 2, map->focal_length);
	map->p_hl = vec_init(-map->viewport_width / 2,
				map->viewport_height / 2, map->focal_length);
	map->p_lr = vec_init(map->viewport_width / 2,
				-map->viewport_height / 2, map->focal_length);
	make_view_plane(map);
	map->vertical = vec_minus(map->p_hl, map->p_ll);
	map->horizontal = vec_minus(map->p_lr, map->p_ll);
}
