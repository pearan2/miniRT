/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: honlee <honlee@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/06 19:03:33 by honlee            #+#    #+#             */
/*   Updated: 2021/01/06 19:52:26 by honlee           ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

void				start_world(t_map_info *map)
{
	map = 0;
	printf("world start!!\n");
}

void				start_make_bmp(t_map_info *map)
{
	map = 0;
	printf("make_bmp start!!\n");
}

int					main(int ac, char **av)
{
	t_map_info			map;
	if (ac == 2)
	{
		if (parse_make_map(&map, av[1]) == -1)
			return (ft_puterror());
		else
			start_world(&map);
	}
	else if (ac == 3 && av[2][0] == '-' && av[2][1] == '-'
					&& av[2][2] == 's' && av[2][3] == 'a'
					&& av[2][4] == 'v' && av[2][5] == 'e'
					&& av[2][6] == 0)
	{
		if (parse_make_map(&map, av[1]) == -1)
			return (ft_puterror());
		else
			start_make_bmp(&map);		
	}
	else
		return (ft_puterror());
	return (0);
}