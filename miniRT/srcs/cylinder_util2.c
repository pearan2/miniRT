/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder_util2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: honlee <honlee@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/13 19:42:16 by honlee            #+#    #+#             */
/*   Updated: 2021/01/14 00:10:27 by honlee           ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

double			cylinder_hit_a(t_data_cylinder *data, t_vec origin, t_vec u_dir)
{
	t_vec			ta;
	t_vec			n;

	origin = vec_init(0, 0, 0);
	n = data->nor;
	ta = vec_minus(u_dir, vec_scala_multi(n, vec_dot(n, u_dir)));
	return (vec_dot(ta, ta));
}

double			cylinder_hit_b(t_data_cylinder *data, t_vec origin, t_vec u_dir)	
{
	t_vec			ta;
	t_vec			tb;
	t_vec			n;
	t_vec			oc;

	n = data->nor;
	ta = vec_minus(u_dir, vec_scala_multi(n, vec_dot(n, u_dir)));
	oc = vec_minus(origin, data->center);
	tb = vec_minus(oc, vec_scala_multi(n, vec_dot(n, oc)));
	return (2.0 * vec_dot(ta, tb));
}

double			cylinder_hit_c(t_data_cylinder *data, t_vec origin, t_vec u_dir)
{
	t_vec			tb;
	t_vec			n;
	t_vec			oc;

	u_dir = vec_init(0, 0, 0);
	n = data->nor;
	oc = vec_minus(origin, data->center);
	tb = vec_minus(oc, vec_scala_multi(n, vec_dot(n, oc)));
	return (vec_dot(tb, tb) - (data->radius * data->radius));
}