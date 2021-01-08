/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rotate_test.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: honlee <honlee@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/07 19:04:03 by honlee            #+#    #+#             */
/*   Updated: 2021/01/07 21:47:03 by honlee           ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"
#include <stdio.h>
#include <math.h>

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

t_vec			rotate_by_unit(t_vec origin, t_vec dir)
{
	t_vec		ret;
	double		theta_base_z;
	double		theta_base_x;
	double		theta_base_y;

	theta_base_z = atan2(dir.y, dir.x) - atan2(origin.y, origin.x);
	theta_base_x = atan2(dir.z, dir.y) - atan2(origin.z, origin.y);
	theta_base_y = atan2(dir.x, dir.z) - atan2(origin.x, origin.z);
	
	printf("xy (base z)theta >> %f\n",theta_base_z * 57.3);
	printf("yz (base x)theta >> %f\n",theta_base_x * 57.3);
	printf("zx (base y)theta >> %f\n",theta_base_y * 57.3);

	ret = origin;
	ret = rotate_by_x(ret, theta_base_x);
	ret = rotate_by_y(ret, theta_base_y);
	ret = rotate_by_z(ret, theta_base_z);

	return (ret);
}

int				main()
{
	t_vec ori;
	ori.x = 0;
	ori.y = 0;
	ori.z = 1;

	t_vec dir;
	dir.x = 0;
	dir.y = 1;
	dir.z = 0;

	printf("atan2 0 0 >> %f\n", atan2(0, 0) * 57.3);
	printf("atan2 -1 0 >> %f\n", atan2(-1, 0) * 57.3);
	printf("atan2 1 0 >> %f\n", atan2(1, 0) * 57.3);
	t_vec rotated = rotate_by_unit(ori, dir);
	printf("x = %f\n",rotated.x);
	printf("y = %f\n",rotated.y);
	printf("z = %f\n",rotated.z);
}