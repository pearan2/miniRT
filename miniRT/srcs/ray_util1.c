/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_util1.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: honlee <honlee@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/06 01:47:28 by honlee            #+#    #+#             */
/*   Updated: 2021/01/10 21:23:22 by honlee           ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

t_vec			ray_at(t_vec origin, t_vec u_dir, double t)
{
	return (vec_plus(origin, vec_scala_multi(u_dir, t)));
}

void			*hit_func_mapper(t_map_info *map, size_t idx)
{
	if (map->objs[idx]->type == sphere)
		return (&sphere_hit);
	else if (map->objs[idx]->type == plane)
		return (&plane_hit);
	else
		return (0);
}

void			*col_func_mapper(t_map_info *map, size_t idx)
{
	if (map->objs[idx]->type == sphere)
		return (&sphere_get_colt);
	else if (map->objs[idx]->type == plane)
		return (&plane_get_colt);
	else
		return (0);
}

double			ray_is_block(t_map_info *map, size_t obj_idx, t_vec origin, t_vec u_dir)
{
	size_t		idx;
	double		(*fp)(void *, t_vec, t_vec);
	double		ret;
	double		t_max;

	idx = 0;
	t_max = DBL_MAX;
	while (idx < map->objs_num)
	{
		if (idx == obj_idx)
		{
			idx++;
			continue;
		}
		fp = hit_func_mapper(map, idx);
		ret = fp(map->objs[idx]->data, origin, u_dir);
		if (ret != -1.0 && ret < t_max)
			t_max = ret;
		idx++;
	}
	if (t_max == DBL_MAX)
		return (-1.0);
	return (t_max);
}