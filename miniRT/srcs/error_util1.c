/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_util1.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: honlee <honlee@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/06 19:16:10 by honlee            #+#    #+#             */
/*   Updated: 2021/01/12 22:15:15 by honlee           ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

int				ft_puterror(int opt)
{
	if (opt == 1)
		perror(strerror(errno));
	write(2, "Error\n", 6);
	return (-1);
}

int				ft_close(int fd, int ret)
{
	close(fd);
	return (ret);
}

int				ft_free2(void *target, void *target2, int ret)
{
	free(target);
	free(target2);
	return (ret);
}

int				ft_free(void *target, int ret)
{
	free(target);
	return (ret);
}

void			map_free(t_map_info *map)
{
	size_t		idx;

	idx = 0;
	while (idx < map->l_iter)
		free(map->lights[idx++]);
	free(map->lights);
	idx = 0;
	while (idx < map->o_iter)
	{
		free(map->objs[idx]->data);
		free(map->objs[idx++]);
	}
	free(map->objs);
}