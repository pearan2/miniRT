/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: honlee <honlee@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/21 17:14:08 by honlee            #+#    #+#             */
/*   Updated: 2021/01/06 18:57:02 by honlee           ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

static size_t	ft_get_next(char const *str, char c, size_t s, int is_s)
{
	size_t		ret;

	ret = 0;
	if (is_s == 1)
	{
		while (str[s + ret] != 0 && str[s + ret] == c)
			ret++;
		return (s + ret);
	}
	else
	{
		while (str[s + ret] != 0 && str[s + ret] != c)
			ret++;
		return (s + ret);
	}
}

static size_t	ft_gt(char const *str, char c)
{
	size_t		s;
	size_t		e;
	size_t		ret;

	e = 0;
	ret = 1;
	while (1)
	{
		s = ft_get_next(str, c, e, 1);
		if (str[s] == 0)
			return (ret);
		else
		{
			ret++;
			e = ft_get_next(str, c, s, 0);
		}
	}
	return (ret);
}

static void		ft_strsecat(char *dest, const char *src, size_t s, size_t e)
{
	size_t		idx;

	idx = 0;
	while (s + idx < e)
	{
		dest[idx] = src[s + idx];
		idx++;
	}
	dest[idx] = 0;
}

static char		**ft_free(char **target, size_t size)
{
	size_t		idx;

	idx = 0;
	while (idx < size)
	{
		free(target[idx]);
		idx++;
	}
	free(target);
	return (NULL);
}

char			**ft_split(char const *str, char c)
{
	size_t		idx1;
	char		**ret;
	size_t		s;
	size_t		e;

	if (str == NULL)
		return (NULL);
	if (!(ret = malloc(sizeof(char *) * (ft_gt(str, c) + 1))))
		return (NULL);
	idx1 = 0;
	e = 0;
	while (1)
	{
		s = ft_get_next(str, c, e, 1);
		if (str[s] == 0)
			break ;
		e = ft_get_next(str, c, s, 0);
		if (!(ret[idx1] = malloc(e - s + 1)))
			return (ft_free(ret, idx1));
		ft_strsecat(ret[idx1], str, s, e);
		idx1++;
	}
	ret[idx1] = 0;
	return (ret);
}
