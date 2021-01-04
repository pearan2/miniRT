/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sphere_util1.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: honlee <honlee@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/04 03:45:47 by honlee            #+#    #+#             */
/*   Updated: 2021/01/04 04:10:46 by honlee           ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

int			sphere_hit(t_vec center, double radius, t_vec origin, t_vec dir)
{
	t_vec		oc;
	double		a;
	double		b;
	double		c;
	double		disc;

	oc = vec_minus(origin, center);
	a = vec_dot(dir, dir);
	b = 2.0 * vec_dot(oc, dir);
	c = vec_dot(oc, oc) - radius * radius;
	disc = b * b - 4 * a * c;
	if (disc > 0)
		return (1);
	return (0);
}