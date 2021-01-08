/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rotate_util1_save.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: honlee <honlee@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/07 19:04:03 by honlee            #+#    #+#             */
/*   Updated: 2021/01/08 02:12:32 by honlee           ###   ########seoul.kr  */
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
	double		ra_z;
	double		ra_x;
	double		ra_y;

	ra_x = atan2(dir.z, dir.y) - atan2(ret.z, ret.y);
	ret = rotate_by_x(ret, ra_x);
	ra_y = atan2(dir.x, dir.z) - atan2(ret.x, ret.z);
	ret = rotate_by_y(ret, ra_y);
	ra_z = atan2(dir.y, dir.x) - atan2(ret.y, ret.x);
	ret = rotate_by_z(ret, ra_z);

	return (ret);
}

void			make_view_plane(t_map_info *map)
{
	
}