/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_util4.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: honlee <honlee@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/06 23:19:15 by honlee            #+#    #+#             */
/*   Updated: 2021/01/13 20:08:37 by honlee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_rt.h"

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
	t->radius = fabs(ft_atod(splited[2]) / 2);
	if (!(m->objs[m->o_iter] = malloc(sizeof(t_obj))))
		return (ft_free(t, -1));
	t->spec_color = color_init(1.0, 1.0, 1.0);
	m->objs[m->o_iter]->type = sphere;
	m->objs[m->o_iter]->data = t;
	m->o_iter++;
	return (0);
}

int				parse_plane(t_map_info *m, char **splited)
{
	t_data_plane		*t;

	if (parse_spl_len(splited) != 4)
		return (-1);
	if (!(t = malloc(sizeof(t_data_plane))))
		return (-1);
	if (parse_vec(ft_split(splited[1], ","), &(t->center)) == -1)
		return (ft_free(t, -1));
	if (parse_vec(ft_split(splited[2], ","), &(t->nor)) == -1)
		return (ft_free(t, -1));
	if (parse_color(ft_split(splited[3], ","), &(t->diff_color)) == -1)
		return (ft_free(t, -1));
	if (!(m->objs[m->o_iter] = malloc(sizeof(t_obj))))
		return (ft_free(t, -1));
	t->spec_color = color_init(1.0, 1.0, 1.0);
	t->nor = vec_to_unit(t->nor);
	m->objs[m->o_iter]->type = plane;
	m->objs[m->o_iter]->data = t;
	m->o_iter++;
	return (0);
}

int				parse_square(t_map_info *m, char **splited)
{
	t_data_square			*t;

	if (parse_spl_len(splited) != 5)
		return (-1);
	if (!(t = malloc(sizeof(t_data_square))))
		return (-1);
	if (parse_vec(ft_split(splited[1], ","), &(t->center)) == -1)
		return (ft_free(t, -1));
	if (parse_vec(ft_split(splited[2], ","), &(t->nor)) == -1)
		return (ft_free(t, -1));
	if (!ft_is_double(splited[3]))
		return (ft_free(t, -1));
	t->side_len = fabs(ft_atod(splited[3]));
	if (parse_color(ft_split(splited[4], ","), &(t->diff_color)) == -1)
		return (ft_free(t, -1));
	if (!(m->objs[m->o_iter] = malloc(sizeof(t_obj))))
		return (ft_free(t, -1));
	t->spec_color = color_init(1.0, 1.0, 1.0);
	t->nor = vec_to_unit(t->nor);
	square_make_data(t);
	m->objs[m->o_iter]->type = square;
	m->objs[m->o_iter]->data = t;
	m->o_iter++;
	return (0);
}

int				parse_cam(t_map_info *map, char **splited)
{
	t_cam		*cam;

	if (parse_spl_len(splited) != 4)
		return (-1);
	if (!(cam = malloc(sizeof(t_cam))))
		return (-1);
	if (parse_vec(ft_split(splited[1], ","), &cam->origin) == -1)
		return (ft_free(cam, -1));
	if (parse_vec(ft_split(splited[2], ","), &cam->orient) == -1)
		return (ft_free(cam, -1));
	if (!ft_is_double(splited[3]))
		return (ft_free(cam, -1));
	if (cam->orient.x == 0 && cam->orient.y == 0 && cam->orient.z == 0)
		return (ft_free(cam, -1));
	cam->fov_horizontal = ft_atod(splited[3]);
	if (cam->fov_horizontal <= 0.0 || cam->fov_horizontal >= 180.0)
		return (ft_free(cam, -1));
	map->cams[map->c_iter] = cam;
	map->c_iter++;
	return (0);
}
