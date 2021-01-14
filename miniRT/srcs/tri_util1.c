/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tri_util1.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: honlee <honlee@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/13 20:15:32 by honlee            #+#    #+#             */
/*   Updated: 2021/01/13 22:37:04 by honlee           ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

int				tri_p_int_tri(t_data_tri *data, t_vec p)
{
	t_vec		base;
	t_vec		to_p;
	t_vec		to_o;

	base = vec_minus(data->p2, data->p1);
	to_o = vec_minus(data->p3, data->p1);
	to_p = vec_minus(p, data->p1);
	if (vec_dot(vec_cross(base, to_o), vec_cross(base, to_p)) <= 0)
		return (0);
	base = vec_minus(data->p3, data->p2);
	to_o = vec_minus(data->p1, data->p2);
	to_p = vec_minus(p, data->p2);
	if (vec_dot(vec_cross(base, to_o), vec_cross(base, to_p)) <= 0)
		return (0);
	base = vec_minus(data->p1, data->p3);
	to_o = vec_minus(data->p2, data->p3);
	to_p = vec_minus(p, data->p3);
	if (vec_dot(vec_cross(base, to_o), vec_cross(base, to_p)) <= 0)
		return (0);
	return (1);
}

double			tri_hit(void *data, t_vec origin, t_vec u_dir)
{
	double		t;
	t_vec		n;
	t_vec		u;
	t_vec		v;
	t_vec		lp;

	n = ((t_data_tri *)data)->nor;
	u = vec_minus(((t_data_tri *)data)->p3, ((t_data_tri *)data)->p1);
	v = vec_minus(((t_data_tri *)data)->p2, ((t_data_tri *)data)->p1);
	t = (vec_dot(n, ((t_data_tri *)data)->p1) - vec_dot(n, origin)) / vec_dot(n, u_dir);
	if (t <= 0)
		return (-1.0);
	lp = vec_plus(origin, vec_scala_multi(u_dir, t));
	if (tri_p_int_tri(data, lp))
		return (t);
	return (-1.0);
}

t_shade			tri_get_colt(t_map_info *map, size_t obj_idx , size_t lig_idx, t_vec origin)
{
	t_shade			ret;
	t_vec			u_dir;
	t_vec			h;
	double			t;
	t_vec			nor;

	nor = ((t_data_tri *)map->objs[obj_idx]->data)->nor;
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