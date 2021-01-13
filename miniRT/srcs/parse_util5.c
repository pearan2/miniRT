/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_util5.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: honlee <honlee@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/12 18:44:03 by honlee            #+#    #+#             */
/*   Updated: 2021/01/13 04:50:31 by honlee           ###   ########seoul.kr  */
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
	t->radius = fabs(ft_atod(splited[4])) / 2;
	t->height = fabs(ft_atod(splited[5]));
	if (!(m->objs[m->o_iter] = malloc(sizeof(t_obj))))
		return (ft_free(t, -1));
	t->nor = vec_to_unit(t->nor);
	t->spec_color = color_init(1.0, 1.0, 1.0);
	m->objs[m->o_iter]->type = cylinder;
	m->objs[m->o_iter]->data = t;
	m->o_iter++;
	return (parse_disk(m, t));
}

int				parse_disk_cy(t_data_cylinder *t, t_data_disk *disk, int opt)
{
	disk->center = t->center;
	disk->nor = vec_scala_multi(t->nor, -1.0);
	disk->diff_color = t->diff_color;
	disk->spec_color = t->spec_color;
	disk->radius = t->radius;
	if (opt == 1)
	{
		disk->center = vec_plus(t->center, vec_scala_multi(t->nor, t->height));
		disk->nor = t->nor;
	}
	return (0);
}

int				parse_disk(t_map_info *m, t_data_cylinder *t)
{
	t_data_disk		*disk1;
	t_data_disk		*disk2;

	if (!(disk1 = malloc(sizeof(t_data_disk))))
		return (-1);
	if (!(disk2 = malloc(sizeof(t_data_disk))))
		return (ft_free(disk1, -1));
	parse_disk_cy(t, disk1, 1);
	parse_disk_cy(t, disk2, 0);
	if (!(m->objs[m->o_iter] = malloc(sizeof(t_obj))))
		return (ft_free2(disk1, disk2, -1));
	m->objs[m->o_iter]->type = disk;
	m->objs[m->o_iter]->data = disk1;
	m->o_iter++;
	if (!(m->objs[m->o_iter] = malloc(sizeof(t_obj))))
		return (ft_free2(disk1, disk2, -1));
	m->objs[m->o_iter]->type = disk;
	m->objs[m->o_iter]->data = disk2;
	m->o_iter++;
	return (0);
}