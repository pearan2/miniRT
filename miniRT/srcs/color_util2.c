/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color_util2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: honlee <honlee@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/04 02:41:12 by honlee            #+#    #+#             */
/*   Updated: 2021/01/06 18:48:03 by honlee           ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

t_color				color_plus(t_color a, t_color b, t_color clamp)
{
	t_color				ret;

	ret.r = fmin(clamp.r, a.r + b.r);
	ret.g = fmin(clamp.g, a.g + b.g);
	ret.b = fmin(clamp.b, a.b + b.b);
	return (ret);
}