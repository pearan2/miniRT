/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_util4.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: honlee <honlee@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/06 23:19:15 by honlee            #+#    #+#             */
/*   Updated: 2021/01/08 04:40:43 by honlee           ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

int				parse_light(t_map_info *m, char **splited)
{
	t_light		*t;
	if (parse_spl_len(splited) != 4)
		return (-1);
	if (!(t = malloc(sizeof(t_light))))
		return (-1);
	if (parse_vec(ft_split(splited[1], ","), &(t->center)) == -1)
		return (ft_free(t, -1));
	if (parse_color(ft_split(splited[3], ","), &(t->color)) == -1)
		return (ft_free(t, -1));
	if (!ft_is_double(splited[2]))
		return (ft_free(t, -1));
	t->ratio = ft_atod(splited[2]);
	t->spec_n = 50.0;
	if (t->ratio < 0.0 || t->ratio > 1.0)
		return (ft_free(t, -1));
	m->lights[m->l_iter] = t;
	m->l_iter++;
	return (0);
}

int				parse_sphere(t_map_info *m, char **splited)
{
	t_data_sphere		*t;
	if (parse_spl_len(splited) != 4)
		return (-1);
	if (!(t = malloc(sizeof(t_data_sphere))))
		return (-1);
	if (parse_vec(ft_split(splited[1], ","), &(t->center)) == -1)
		return (ft_free(t, -1));
	if (parse_color(ft_split(splited[3], ","), &(t->diff_color)) == -1)
		return (ft_free(t, -1));
	if (!ft_is_double(splited[2]))
		return (ft_free(t, -1));
	t->radius = ft_atod(splited[2]) / 2;
	if (!(m->objs[m->o_iter] = malloc(sizeof(t_obj))))
		return (ft_free(t, -1));
	t->spec_color = color_init(1.0, 1.0, 1.0);
	m->objs[m->o_iter]->type = sphere;
	m->objs[m->o_iter]->data = t;
	m->o_iter++;
	return (0);
}

int				parse_cam(t_map_info *map, char **splited)
{
	if (parse_spl_len(splited) != 4)
		return (-1);
	if (parse_vec(ft_split(splited[1], ","), &map->origin) == -1)
		return (-1);
	if (parse_vec(ft_split(splited[2], ","), &map->orient) == -1)
		return (-1);
	if (!ft_is_double(splited[3]))
		return (-1);
	map->fov_horizontal = ft_atod(splited[3]);
	if (map->fov_horizontal < 0.0 || map->fov_horizontal > 180.0)
		return (-1);
	map->c_cnt++;
	return (0);
}