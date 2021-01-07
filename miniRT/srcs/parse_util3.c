/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_util3.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: honlee <honlee@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/06 22:57:50 by honlee            #+#    #+#             */
/*   Updated: 2021/01/07 04:25:51 by honlee           ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

int				parse_col_check(t_color col)
{
	if (col.r < 0.0 || col.r > 1.0
		|| col.g < 0.0 || col.g > 1.0
		|| col.b < 0.0 || col.b > 1.0)
		return (-1);
	return (0);
}

int				parse_color(char **splited, t_color *col)
{
	size_t		idx;

	if ((idx = parse_spl_len(splited)) != 3)
	{
		ft_split_free(splited, idx);
		return (-1);
	}
	col->r = (double)ft_atoi(splited[0]) / (double)255;
	col->g = (double)ft_atoi(splited[1]) / (double)255;
	col->b = (double)ft_atoi(splited[2]) / (double)255;
	ft_split_free(splited, idx);
	return (parse_col_check(*col));	
}

int				parse_vec(char **splited, t_vec *vec)
{
	size_t		idx;

	if ((idx = parse_spl_len(splited)) != 3)
	{
		ft_split_free(splited, idx);
		return (-1);
	}
	if (!ft_is_double(splited[0])
		|| !ft_is_double(splited[1])
		|| !ft_is_double(splited[2]))
		return (-1);
	vec->x = ft_atod(splited[0]);
	vec->y = ft_atod(splited[1]);
	vec->z = ft_atod(splited[2]);
	ft_split_free(splited, idx);
	return (0);
}