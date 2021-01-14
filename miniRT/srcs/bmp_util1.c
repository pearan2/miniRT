/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bmp_util1.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: honlee <honlee@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/13 23:40:42 by honlee            #+#    #+#             */
/*   Updated: 2021/01/14 01:13:35 by honlee           ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

t_bmfh			bmp_get_file_header(t_map_info *m)
{
	t_bmfh			ret;

	ret.id1 = 'B';
	ret.id2 = 'M';
	ret.size = 54 + 4 * m->image_width * m->image_height;
	ret.reserved1 = 0;
	ret.reserved2 = 0;
	ret.offset = 54;
	return (ret);
}

t_bmih			bmp_get_info_header(t_map_info *m)
{
	t_bmih			ret;

	ret.size = 40;
	ret.width = m->image_width;
	ret.height = m->image_height;
	ret.planes = 1;
	ret.bit_count = 24;
	ret.compression = 0;
	ret.bit_size = 4 * m->image_width * m->image_height;
	ret.x_pels_per_meter = m->image_width;
	ret.y_pels_per_meter = m->image_height;
	ret.color_used = 0xffffff;
	ret.color_important = 0;
	return (ret);
}

t_rgbt			bmp_get_rgbt_by_color(t_color color)
{
	t_rgbt			ret;

	ret.blue = (unsigned char)(color.b * 255.0);
	ret.green = (unsigned char)(color.g * 255.0);
	ret.red = (unsigned char)(color.r * 255.0);
	return (ret);
}