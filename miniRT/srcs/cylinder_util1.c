/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder_util1.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: honlee <honlee@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/12 19:00:11 by honlee            #+#    #+#             */
/*   Updated: 2021/01/13 05:05:55 by honlee           ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

double			cylinder_hit(void *data, t_vec origin, t_vec u_dir)
{
	double		t;
	double		h;
	double		a;
	double		b;
	double		c;
	double		r;
	t_vec		ta;
	t_vec		tb;	
	t_vec		n;
	t_vec		ct;
	double		disc;
	t_vec		oc;

	n = ((t_data_cylinder *)data)->nor;
	ct = ((t_data_cylinder *)data)->center;
	r = ((t_data_cylinder *)data)->radius;

	ta = vec_minus(u_dir, vec_scala_multi(n, vec_dot(n, u_dir)));
	oc = vec_minus(origin, ct);
	tb = vec_minus(oc, vec_scala_multi(n, vec_dot(n, oc)));
	a = vec_dot(ta, ta);
	b = 2.0 * vec_dot(ta, tb);
	c = vec_dot(tb, tb) - (r * r);
	disc = (b * b) - (4 * a * c);
	if (disc <= 0)
		return (-1.0);
	t = (-b - sqrt(disc)) / (2.0 * a);
	if (t < 0.001)
		return (-1.0);
	h = t * vec_dot(n, u_dir) + vec_dot(vec_minus(origin, ct), n);
	if (h >= 0 && h <= ((t_data_cylinder *)data)->height)
		return (t);
	return (-1.0);
}

t_vec			cylinder_get_nor(t_data_cylinder *data, t_vec origin)
{
	double			h;
	t_vec			ph;
	t_vec			ret;

	h = vec_dot(vec_minus(origin, data->center), data->nor);
	ph = vec_plus(data->center, vec_scala_multi(data->nor, h));
	ret = vec_minus(origin, ph);

	return (ret);
}

t_shade			cylinder_get_colt(t_map_info *map, size_t obj_idx , size_t lig_idx, t_vec origin)
{
	t_shade			ret;
	t_vec			u_dir;
	t_vec			h;
	double			t;
	t_vec			nor;
	double			th;

	nor = cylinder_get_nor(map->objs[obj_idx]->data, origin);
	ret = shade_init(0, 0, 0);
	u_dir = vec_to_unit(vec_minus(map->lights[lig_idx]->center, origin));
	t = ((map->lights[lig_idx]->center.x) - origin.x) / (u_dir.x);
	if (ray_is_block(map, obj_idx, origin, u_dir) != -1.0 &&
			ray_is_block(map, obj_idx, origin, u_dir) < t)
		return (ret);
	ret.diff_ratio = map->lights[lig_idx]->ratio * fmax(0, vec_dot(u_dir, nor));
	h = vec_to_unit(vec_minus(map->origin, origin));
	h = vec_to_unit(vec_plus(u_dir, h));
	ret.spec_ratio = pow(fmax(0, vec_dot(h, nor)), map->lights[lig_idx]->spec_n);
	return (ret);
}