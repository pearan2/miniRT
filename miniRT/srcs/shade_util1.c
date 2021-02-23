/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shade_util1.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: honlee <honlee@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/06 18:00:42 by honlee            #+#    #+#             */
/*   Updated: 2021/01/11 18:46:04 by honlee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_rt.h"

t_shade				shade_init(t_color a, double b, double c)
{
	t_shade			ret;

	ret.diff_ratio = a;
	ret.spec_ratio = b;
	ret.som_ratio = c;
	return (ret);
}

t_shade				shade_plus(t_shade a, t_shade b)
{
	t_shade			ret;

	ret.diff_ratio = color_plus(a.diff_ratio, b.diff_ratio,
						color_init(1.0, 1.0, 1.0));
	ret.spec_ratio = a.spec_ratio + b.spec_ratio;
	ret.som_ratio = a.som_ratio + b.som_ratio;
	return (ret);
}
