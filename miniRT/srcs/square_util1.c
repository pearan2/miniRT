/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   square_util1.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: honlee <honlee@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/11 18:56:12 by honlee            #+#    #+#             */
/*   Updated: 2021/01/12 19:00:26 by honlee           ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

void				square_rotate(t_data_square *data)
{
	double		ra_x;
	double		ra_y;
	double		ra_z;

	ra_x = atan2(data->nor.z, data->nor.y) - atan2(data->center.z, data->center.y);
	data->center = rotate_by_x(data->center, ra_x);
	data->ll = rotate_by_x(data->ll, ra_x);
	data->lr = rotate_by_x(data->lr, ra_x);
	data->hl = rotate_by_x(data->hl, ra_x);

	ra_y = atan2(data->nor.x, data->nor.z) - atan2(data->center.x, data->center.z);
	data->center = rotate_by_y(data->center, ra_y);
	data->ll = rotate_by_y(data->ll, ra_y);
	data->lr = rotate_by_y(data->lr, ra_y);
	data->hl = rotate_by_y(data->hl, ra_y);

	ra_z = atan2(data->nor.y, data->nor.x) - atan2(data->center.y, data->center.x);
	data->center = rotate_by_z(data->center, ra_z);
	data->ll = rotate_by_z(data->ll, ra_z);
	data->lr = rotate_by_z(data->lr, ra_z);
	data->hl = rotate_by_z(data->hl, ra_z);	
}

void				square_make_data(t_data_square *data)
{
	t_vec			center;
	size_t			idx;
	t_vec			diff;

	center = data->center;
	data->center = vec_init(0, 0, 1);
	data->ll = vec_init(-data->side_len/2, -data->side_len/2, 1);
	data->hl = vec_init(-data->side_len/2, data->side_len/2, 1);
	data->lr = vec_init(data->side_len/2, -data->side_len/2, 1);
	idx = 0;
	while (++idx < 30)
		square_rotate(data);
	diff = vec_minus(center, data->center);
	data->center = vec_plus(data->center, diff);
	data->ll = vec_plus(data->ll, diff);
	data->lr = vec_plus(data->lr, diff);
	data->hl = vec_plus(data->hl, diff);
	data->vertical = vec_minus(data->hl, data->ll);
	data->horizontal = vec_minus(data->lr, data->ll);
}

double			square_hit(void *data, t_vec origin, t_vec u_dir)
{
	double		t;
	t_vec		n;
	t_vec		lp;
	t_vec		hori;
	t_vec		ver;

	n = ((t_data_square *)data)->nor;
	hori = ((t_data_square *)data)->horizontal;
	ver = ((t_data_square *)data)->vertical;
	t = (vec_dot(n, ((t_data_square *)data)->center) - vec_dot(n, origin)) / vec_dot(n, u_dir);
	if (t <= 0)
		return (-1.0);
	lp = vec_plus(origin, vec_scala_multi(u_dir, t));
	lp = vec_minus(lp, ((t_data_square *)data)->ll);
	if (vec_dot(lp, vec_to_unit(hori)) <= vec_length(hori) && vec_dot(lp, hori) >= 0
		&& vec_dot(lp, vec_to_unit(ver)) <= vec_length(ver) && vec_dot(lp, ver) >= 0)
		return (t);
	return (-1.0);
}

t_shade			square_get_colt(t_map_info *map, size_t obj_idx , size_t lig_idx, t_vec origin)
{
	t_shade			ret;
	t_vec			u_dir;
	t_vec			h;
	double			t;
	t_vec			nor;

	nor = ((t_data_square *)map->objs[obj_idx]->data)->nor;
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