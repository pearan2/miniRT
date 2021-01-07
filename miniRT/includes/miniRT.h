/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   miniRT.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: honlee <honlee@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/03 22:35:51 by honlee            #+#    #+#             */
/*   Updated: 2021/01/06 20:15:52 by honlee           ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_H
# define MINIRT_H

# include <mlx.h>
# include <math.h>
# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include <stdio.h>
# include <float.h>

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

typedef struct			s_shade
{
	double				diff_ratio;
	double				spec_ratio;
	double				som_ratio;
}						t_shade;

typedef enum			e_obj_type
{
	sphere,
	triangle,
	cylinder,
	square,
	plane
}						t_obj_type;

typedef struct			s_obj
{
	void *				data;
	t_obj_type			type;
}						t_obj;

typedef struct			s_data_sphere
{
	t_vec				center;
	double				radius;
	t_color				diff_color;
	t_color				spec_color;
	t_color				ambi_color;
}						t_data_sphere;

typedef struct			s_light
{
	t_vec				center;
	t_color				color;
	double				ratio;
	double				spec_n;
}						t_light;

typedef struct			s_map_info
{
	double				apsect_ratio;
	int					image_width;
	int					image_height;
	double				viewport_height;
	double				viewport_width;
	double				focal_length;
	t_vec				origin;
	t_vec				horizontal;
	t_vec				vertical;
	t_vec				lower_left_corner;
	t_obj				**objs;
	t_light				**lights;
	t_light				ambient;
	size_t				objs_num;
	size_t				lights_num;
}						t_map_info;

int					get_next_line(int fd, char **line);
char				**ft_split(char const *str, char c);
int					ft_atoi(const char *str);
double				ft_atod(const char *str);
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
t_color				color_scala_multi(t_color a, double t, t_color clamp);
t_color				color_init(double r, double g, double b);
t_color				color_plus(t_color a, t_color b, t_color clamp);
double				sphere_hit(void *data, t_vec origin, t_vec dir);
t_vec				sphere_get_nor(t_data_sphere *data, t_vec origin, t_vec u_dir, double t);
t_vec				ray_at(t_vec origin, t_vec u_dir, double t);
t_shade				sphere_get_colt(t_map_info *map, size_t obj_idx , size_t lig_idx, t_vec origin);
double				ray_is_block(t_map_info *map, size_t obj_idx, t_vec origin, t_vec u_dir);
t_shade				shade_init(double a, double b, double c);
t_shade				shade_plus(t_shade a, t_shade b);
int					ft_puterror(void);
int					parse_make_map(t_map_info *map, const char *path);
#endif