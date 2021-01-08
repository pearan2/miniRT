/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color_util2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: honlee <honlee@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/04 02:41:12 by honlee            #+#    #+#             */
/*   Updated: 2021/01/08 05:03:04 by honlee           ###   ########seoul.kr  */
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

t_color				get_hit_col(t_map_info *map, t_vec unit_dir, double t_max, size_t hit_idx)
{
	t_color			diff_col;
	t_color			spec_col;
	size_t			idx;
	t_shade			shader;
	t_vec			ori;

	idx = 0;
	shader = shade_init(0, 0, 0);
	ori = ray_at(map->origin, unit_dir, t_max);
	while (idx < map->lights_num)
		shader = shade_plus(shader, sphere_get_colt(map, hit_idx, idx++, ori));
	diff_col = ((t_data_sphere *)map->objs[hit_idx]->data)->diff_color;
	spec_col = ((t_data_sphere *)map->objs[hit_idx]->data)->spec_color;
	diff_col = color_scala_multi(diff_col, shader.diff_ratio, diff_col);
	spec_col = color_scala_multi(spec_col, shader.spec_ratio, color_init(1.0, 1.0, 1.0));
	return (color_plus(diff_col, spec_col, color_init(1.0, 1.0, 1.0)));
}