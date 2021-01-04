/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color_util1.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: honlee <honlee@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/04 01:28:54 by honlee            #+#    #+#             */
/*   Updated: 2021/01/04 02:38:30 by honlee           ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

t_color			color_int_to_col(int r, int g, int b)
{
	t_color				ret;
	ret.r = (double)r / (double)255;
	ret.g = (double)g / (double)255;
	ret.b = (double)b / (double)255;
	return (ret);
}

t_color			color_dbl_to_col(double r, double g, double b)
{
	t_color				ret;
	ret.r = r;
	ret.g = g;
	ret.b = b;
	return (ret);
}

int				color_col_to_int(t_color col)
{
	int r;
	int g;
	int b;
	int ret;

	r = col.r * 255;
	g = col.g * 255;
	b = col.b * 255;
	ret = r;
	ret = (ret << 8) + g;
	ret = (ret << 8) + b;
	return (ret);
}

t_color			color_scala_multi(t_color a, double t)
{
	t_color				ret;

	ret.r = a.r * t;
	ret.b = a.b * t;
	ret.g = a.g * t;
	return (ret);
}

t_color			color_init(double r, double g, double b)
{
	t_color				ret;

	ret.r = r;
	ret.g = g;
	ret.b = b;
	retrun (ret);
}