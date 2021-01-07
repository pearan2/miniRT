/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: honlee <honlee@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/21 13:55:48 by honlee            #+#    #+#             */
/*   Updated: 2020/12/22 13:10:45 by honlee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int			ft_atoi(const char *str)
{
	unsigned int		ret;
	unsigned int		is_minus;

	ret = 0;
	is_minus = 0;
	while ((*str <= '\r' && *str >= '\t') || *str == ' ')
		str++;
	if (*str == '-' || *str == '+')
	{
		if (*str == '-')
			is_minus = 1;
		str++;
	}
	while (*str <= '9' && *str >= '0')
		ret = (ret * 10) + (*str++) - '0';
	if (is_minus)
		return (ret * (-1));
	return (ret);
}
