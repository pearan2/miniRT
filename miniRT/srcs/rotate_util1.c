/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rotate_util1.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: honlee <honlee@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/07 19:04:03 by honlee            #+#    #+#             */
/*   Updated: 2021/01/08 02:18:39 by honlee           ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

t_vec			rotate_by_x(t_vec origin, double theta_base_x)
{
	t_vec			ret;

	ret.x = origin.x;
	ret.y = origin.y * cos(theta_base_x) - origin.z * sin(theta_base_x);
	ret.z = origin.y * sin(theta_base_x) + origin.z * cos(theta_base_x);
	return (ret);
}

t_vec			rotate_by_y(t_vec origin, double theta_base_y)
{
	t_vec			ret;

	ret.x = origin.z * sin(theta_base_y) + origin.x * cos(theta_base_y);
	ret.y = origin.y;
	ret.z = origin.z * cos(theta_base_y) - origin.x * sin(theta_base_y);
	return (ret);
}

t_vec			rotate_by_z(t_vec origin, double theta_base_z)
{
	t_vec			ret;

	ret.x = origin.x * cos(theta_base_z) - origin.y * sin(theta_base_z);
	ret.y = origin.x * sin(theta_base_z) + origin.y * cos(theta_base_z);
	ret.z = origin.z;
	return (ret);
}

void			rotate_by_unit(t_map_info *map)
{
	double		ra_x;
	double		ra_y;
	double		ra_z;

	ra_x = atan2(map->orient.z, map->orient.y) - atan2(map->p_c.z, map->p_c.y);
	map->p_c = rotate_by_x(map->p_c, ra_x);
	map->p_ll = rotate_by_x(map->p_ll, ra_x);
	map->p_lr = rotate_by_x(map->p_lr, ra_x);
	map->p_hl = rotate_by_x(map->p_hl, ra_x);
	ra_y = atan2(map->orient.x, map->orient.z) - atan2(map->p_c.x, map->p_c.z);
	map->p_c = rotate_by_y(map->p_c, ra_y);
	map->p_ll = rotate_by_y(map->p_ll, ra_y);
	map->p_lr = rotate_by_y(map->p_lr, ra_y);
	map->p_hl = rotate_by_y(map->p_hl, ra_y);
	ra_z = atan2(map->orient.y, map->orient.x) - atan2(map->p_c.y, map->p_c.x);
	map->p_c = rotate_by_y(map->p_c, ra_z);
	map->p_ll = rotate_by_y(map->p_ll, ra_z);
	map->p_lr = rotate_by_y(map->p_lr, ra_z);
	map->p_hl = rotate_by_y(map->p_hl, ra_z);
}

void			make_view_plane(t_map_info *map)
{
	size_t			idx;

	idx = 0;
	while (idx++ < 30)
		rotate_by_unit(map);
}