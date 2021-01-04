/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec_util2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: honlee <honlee@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/03 22:53:19 by honlee            #+#    #+#             */
/*   Updated: 2021/01/04 01:14:13 by honlee           ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

double			vec_length_squared(t_vec a)
{
	return (a.x * a.x + a.y * a.y + a.z * a.z);
}

double			vec_length(t_vec a)
{
	return (sqrt(vec_length_squared(a)));
}

t_vec			vec_scala_multi(t_vec a, double t)
{
	t_vec				ret;
	ret.x = a.x * t;
	ret.y = a.y * t;
	ret.z = a.z * t;
	return (ret);
}

t_vec			vec_init(double x, double y, double z)
{
	t_vec				ret;
	ret.x = x;
	ret.y = y;
	ret.z = z;
	return (ret);
}