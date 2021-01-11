/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   plane_util1.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: honlee <honlee@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/10 17:39:25 by honlee            #+#    #+#             */
/*   Updated: 2021/01/11 00:33:09 by honlee           ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

double			plane_hit(void *data, t_vec origin, t_vec u_dir)
{
	double		t;
	t_vec		p;
	t_vec		n;

	p = ((t_data_plane *)data)->center;
	n = ((t_data_plane *)data)->nor;
	t = (vec_dot(n, p) - vec_dot(n, origin)) / vec_dot(n, u_dir);
	if (t <= 0)
		return (-1.0);
	return (t);
}

t_shade			plane_get_colt(t_map_info *map, size_t obj_idx , size_t lig_idx, t_vec origin)
{
	t_shade			ret;
	t_vec			u_dir;
	t_vec			h;
	double			t;
	t_vec			nor;

	nor = ((t_data_plane *)map->objs[obj_idx]->data)->nor;
	ret = shade_init(0, 0, 0);
	u_dir = vec_to_unit(vec_minus(map->lights[lig_idx]->center, origin));
	t = ((map->lights[lig_idx]->center.x) - origin.x) / (u_dir.x);
	if (ray_is_block(map, obj_idx, origin, u_dir) != -1.0 &&
			ray_is_block(map, obj_idx, origin, u_dir) < t)
		return (ret);
	ret.diff_ratio = map->lights[lig_idx]->ratio * fmax(0, fabs(vec_dot(u_dir, nor)));
	h = vec_to_unit(vec_minus(map->origin, origin));
	h = vec_to_unit(vec_plus(u_dir, h));
	ret.spec_ratio = pow(fmax(0, fabs(vec_dot(h, nor))), map->lights[lig_idx]->spec_n);
	return (ret);
}