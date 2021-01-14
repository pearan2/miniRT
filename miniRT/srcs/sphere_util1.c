/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sphere_util1.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: honlee <honlee@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/04 03:45:47 by honlee            #+#    #+#             */
/*   Updated: 2021/01/10 22:05:57 by honlee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_rt.h"

double			sphere_hit(void *data, t_vec origin, t_vec u_dir)
{
	t_vec		oc;
	double		a;
	double		b;
	double		c;
	double		disc;

	oc = vec_minus(origin, ((t_data_sphere *)data)->center);
	a = vec_dot(u_dir, u_dir);
	b = 2.0 * vec_dot(oc, u_dir);
	if (b > 0)
		return (-1.0);
	c = vec_dot(oc, oc) - (((t_data_sphere *)data)->radius *
									((t_data_sphere *)data)->radius);
	disc = (b * b) - (4 * a * c);
	if (disc <= 0)
		return (-1.0);
	return ((-b - sqrt(disc)) / (2.0 * a));
}

t_vec			sphere_get_nor(t_data_sphere *data, t_vec origin,
											t_vec u_dir, double t)
{
	t_vec			ret;

	ret = ray_at(origin, u_dir, t);
	ret = vec_minus(ret, data->center);
	ret = vec_to_unit(ret);
	return (ret);
}

t_shade			sphere_get_colt(t_map_info *map, size_t obj_idx,
											size_t lig_idx, t_vec origin)
{
	t_vec			nor;
	t_vec			u_dir;
	t_shade			ret;
	t_vec			h;
	double			t;

	ret = shade_init(0, 0, 0);
	u_dir = vec_minus(map->lights[lig_idx]->center, origin);
	u_dir = vec_to_unit(u_dir);
	t = ((map->lights[lig_idx]->center.x) - origin.x) / (u_dir.x);
	nor = vec_minus(origin,
				((t_data_sphere *)map->objs[obj_idx]->data)->center);
	nor = vec_to_unit(nor);
	if (ray_is_block(map, obj_idx, origin, u_dir) != -1.0 &&
			ray_is_block(map, obj_idx, origin, u_dir) < t)
		return (ret);
	ret.diff_ratio = map->lights[lig_idx]->ratio * fmax(0, vec_dot(u_dir, nor));
	h = vec_to_unit(vec_minus(map->origin, origin));
	h = vec_to_unit(vec_plus(u_dir, h));
	ret.spec_ratio = pow(fmax(0, vec_dot(h, nor)),
								map->lights[lig_idx]->spec_n);
	return (ret);
}
