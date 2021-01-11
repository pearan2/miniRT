/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color_util2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: honlee <honlee@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/04 02:41:12 by honlee            #+#    #+#             */
/*   Updated: 2021/01/10 22:44:03 by honlee           ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

t_color				color_plus(t_color a, t_color b, t_color clamp)
{
	t_color				ret;

	ret.r = fmin(clamp.r, a.r + b.r);
	ret.g = fmin(clamp.g, a.g + b.g);
	ret.b = fmin(clamp.b, a.b + b.b);
	return (ret);
}

t_color				get_diff_col(t_map_info *map, size_t idx)
{
	if (map->objs[idx]->type == sphere)
		return (((t_data_sphere *)map->objs[idx]->data)->diff_color);
	else if (map->objs[idx]->type == plane)
		return (((t_data_plane *)map->objs[idx]->data)->diff_color);
	else
		return (color_init(0, 0, 0));
}

t_color				get_spec_col(t_map_info *map, size_t idx)
{
	if (map->objs[idx]->type == sphere)
		return (((t_data_sphere *)map->objs[idx]->data)->spec_color);
	else if (map->objs[idx]->type == plane)
		return (((t_data_plane *)map->objs[idx]->data)->spec_color);
	else
		return (color_init(0, 0, 0));
}

t_color				get_hit_col(t_map_info *map, t_vec unit_dir, double t_max, size_t hit_idx)
{
	t_color			diff_col;
	t_color			spec_col;
	size_t			idx;
	t_shade			shader;
	t_shade			(*fp)(t_map_info *, size_t, size_t, t_vec);

	idx = 0;
	shader = shade_init(0, 0, 0);
	fp = col_func_mapper(map, hit_idx);
	while (idx < map->lights_num)
		shader = shade_plus(shader, fp(map, hit_idx, idx++, ray_at(map->origin, unit_dir, t_max)));
	diff_col = get_diff_col(map, hit_idx);
	spec_col = get_spec_col(map, hit_idx);
	diff_col = color_scala_multi(diff_col, shader.diff_ratio + map->ambient.ratio, diff_col);
	spec_col = color_scala_multi(spec_col, shader.spec_ratio, color_init(1.0, 1.0, 1.0));
	return (color_plus(diff_col, spec_col, color_init(1.0, 1.0, 1.0)));
}