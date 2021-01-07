/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: honlee <honlee@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/07 02:14:49 by honlee            #+#    #+#             */
/*   Updated: 2021/01/07 02:19:42 by honlee           ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include <stdio.h>

#define PI 3.1415926535897

double getRadian(double num)
{
	return (num * (PI / 180));
}

int			main()
{
	double ra = getRadian(45.0);
	printf("%f\n", tan(ra));
}