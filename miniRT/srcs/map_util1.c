/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_util1.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: honlee <honlee@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/06 19:03:33 by honlee            #+#    #+#             */
/*   Updated: 2021/01/14 03:42:13 by honlee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_rt.h"

void			map_init(t_map_info *map)
{
	map->r_cnt = 0;
	map->c_cnt = 0;
	map->a_cnt = 0;
	map->n_c_idx = 0;
}

int				rt_checker(char *str)
{
	size_t		idx;

	idx = 0;
	while (str[idx] != 0)
		idx++;
	if (!(str[idx - 3] == '.' && str[idx - 2] == 'r'
			&& str[idx - 1] == 't'))
		return (-1);
	return (0);
}
