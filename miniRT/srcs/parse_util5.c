/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_util5.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: honlee <honlee@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/12 18:44:03 by honlee            #+#    #+#             */
/*   Updated: 2021/01/12 19:00:08 by honlee           ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

int				parse_cylinder(t_map_info *m, char **splited)
{
	t_data_cylinder		*t;

	if (parse_spl_len(splited) != 6)
		return (-1);
	if (!(t = malloc(sizeof(t_data_cylinder))))
		return (-1);
	if (parse_vec(ft_split(splited[1], ","), &(t->center)) == -1)
		return (ft_free(t, -1));
	if (parse_vec(ft_split(splited[2], ","), &(t->nor)) == -1)
		return (ft_free(t, -1));
	if (parse_color(ft_split(splited[3], ","), &(t->diff_color)) == -1)
		return (ft_free(t, -1));
	if (!ft_is_double(splited[4]) || !ft_is_double(splited[5]))
		return (ft_free(t, -1));
	t->radius = ft_atod(splited[4]);
	t->height = ft_atod(splited[5]);
	return (0);
}