/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   convert_util1.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: honlee <honlee@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/21 13:55:48 by honlee            #+#    #+#             */
/*   Updated: 2021/01/07 04:25:48 by honlee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_rt.h"

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

int			ft_is_double(const char *str)
{
	int			num_of_point;
	size_t		idx;

	idx = 0;
	num_of_point = 0;
	if (str[idx] == '-')
		idx++;
	while (str[idx] != 0)
	{
		if (!(str[idx] <= '9' && str[idx] >= '0'))
		{
			if (str[idx] == '.')
			{
				num_of_point++;
				if (num_of_point != 1)
					return (0);
			}
			else
				return (0);
		}
		idx++;
	}
	if (idx == 0 || (idx == 1 && str[0] == '-'))
		return (0);
	return (1);
}

double		ft_atod(const char *str)
{
	double				ret;
	double				div;
	int					is_minus;

	ret = 0;
	div = 10.0;
	is_minus = 0;
	if (*str == '-')
	{
		is_minus = 1;
		str++;
	}
	while (*str != '.' && *str != 0)
		ret = (ret * 10.0) + (double)(*(str++) - '0');
	if (*str == 0)
		return (is_minus == 0 ? ret : (-1.0) * ret);
	str++;
	while (*str != 0)
	{
		ret += (double)(*(str++) - '0') / div;
		div = div * 10.0;
	}
	return (is_minus == 0 ? ret : (-1.0) * ret);
}

double		ft_to_radian(double input)
{
	return (input * (PI / 180));
}

double		ft_to_degree(double input)
{
	return (input * 57.3);
}
