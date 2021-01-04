/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   miniRT.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: honlee <honlee@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/03 22:35:51 by honlee            #+#    #+#             */
/*   Updated: 2021/01/04 04:10:44 by honlee           ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_H
# define MINIRT_H

# include <mlx.h>
# include <math.h>

typedef struct			s_data
{
	void				*img;
	char				*addr;
	int					bits_per_pixel;
	int					line_length;
	int					endian;
}						t_data;

typedef struct			s_color
{
	double				r;
	double				g;
	double				b;
}						t_color;

typedef struct          s_vec
{
    double              x;
    double              y;
    double              z;
}                       t_vec;

double				vec_length_squared(t_vec a);
double				vec_length(t_vec a);
double				vec_dot(t_vec a, t_vec b);
t_vec				vec_multi(t_vec a, t_vec b);
t_vec				vec_minus(t_vec a, t_vec b);
t_vec				vec_plus(t_vec a, t_vec b);
t_vec				vec_init(double x, double y, double z);
t_vec				vec_to_unit(t_vec a);
void				ft_mlx_pixel_put(t_data *data, int x, int y, t_color col);
t_vec				vec_scala_multi(t_vec a, double t);
t_color				color_int_to_col(int r, int g, int b);
t_color				color_dbl_to_col(double r, double g, double b);
int					color_col_to_int(t_color col);
t_color				color_scala_multi(t_color a, double t);
t_color				color_init(double r, double g, double b);
t_color				color_plus(t_color a, t_color b);
int					sphere_hit(t_vec center, double radius, t_vec origin, t_vec dir);

#endif