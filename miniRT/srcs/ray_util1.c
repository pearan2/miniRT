/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_util1.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: honlee <honlee@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/06 01:47:28 by honlee            #+#    #+#             */
/*   Updated: 2021/01/06 18:48:07 by honlee           ###   ########seoul.kr  */
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
	else
		return (0);
}

double			ray_is_block(t_map_info *map, size_t obj_idx, t_vec origin, t_vec u_dir)
{
	size_t		idx;
	double		(*fp)(void *, t_vec, t_vec);
	double		ret;

	idx = 0;
	while (idx < map->objs_num)
	{
		if (idx == obj_idx)
		{
			idx++;
			continue;
		}
		fp = hit_func_mapper(map, idx);
		ret = fp(map->objs[idx]->data, origin, u_dir);
		if (ret != -1.0)
			return (ret);
		idx++;
	}
	return (-1.0);
}