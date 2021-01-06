/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec_util1.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: honlee <honlee@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/03 22:42:11 by honlee            #+#    #+#             */
/*   Updated: 2021/01/05 23:41:21 by honlee           ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

t_vec			vec_plus(t_vec a, t_vec b)
{
    t_vec			ret;
    ret.x = a.x + b.x;
    ret.y = a.y + b.y;
    ret.z = a.z + b.z;
    return (ret);
}

t_vec			vec_minus(t_vec a, t_vec b)
{
    t_vec			ret;
	ret.x = a.x - b.x;
	ret.y = a.y - b.y;
	ret.z = a.z - b.z;
	return (ret);
}

t_vec			vec_multi(t_vec a, t_vec b)
{
	t_vec			ret;
	ret.x = a.x * b.x;
	ret.y = a.y * b.y;
	ret.z = a.z * b.z;
	return (ret);
}

double			vec_dot(t_vec a, t_vec b)
{
	return (a.x * b.x + a.y * b.y + a.z * b.z);
}

t_vec			vec_to_unit(t_vec a)
{
	t_vec			ret;
	double			div;

	div = vec_length(a);
	ret.x = a.x / div;
	ret.y = a.y / div;
	ret.z = a.z / div;
	return (ret);
}