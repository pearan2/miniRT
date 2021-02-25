/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_rt.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: honlee <honlee@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/03 22:35:51 by honlee            #+#    #+#             */
/*   Updated: 2021/01/14 01:01:35 by honlee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINI_RT_H
# define MINI_RT_H

# include <stdio.h>
# include <mlx.h>
# include <math.h>
# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include <stdio.h>
# include <float.h>
# include <string.h>
# include <errno.h>

# define PI 3.1415926535897

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

typedef struct			s_vec
{
	double				x;
	double				y;
	double				z;
}						t_vec;

typedef struct			s_shade
{
	t_color				diff_ratio;
	double				spec_ratio;
	double				som_ratio;
}						t_shade;

typedef enum			e_obj_type
{
	sphere,
	triangle,
	cylinder,
	square,
	plane,
	disk
}						t_obj_type;

typedef struct			s_obj
{
	void				*data;
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

typedef struct			s_data_plane
{
	t_vec				center;
	t_vec				nor;
	t_color				diff_color;
	t_color				spec_color;
	t_color				ambi_color;
}						t_data_plane;

typedef struct			s_data_square
{
	t_vec				ll;
	t_vec				lr;
	t_vec				hl;
	t_vec				vertical;
	t_vec				horizontal;
	t_vec				nor;
	t_vec				center;
	t_color				diff_color;
	t_color				ambi_color;
	t_color				spec_color;
	double				side_len;
}						t_data_square;

typedef struct			s_data_disk
{
	t_vec				center;
	t_vec				nor;
	double				radius;
	t_color				diff_color;
	t_color				spec_color;
}						t_data_disk;

typedef struct			s_data_cylinder
{
	t_vec				center;
	t_vec				nor;
	double				height;
	double				radius;
	t_color				diff_color;
	t_color				spec_color;
}						t_data_cylinder;

typedef struct			s_cam
{
	t_vec				origin;
	t_vec				orient;
	double				fov_horizontal;
}						t_cam;

typedef struct			s_data_tri
{
	t_vec				p1;
	t_vec				p2;
	t_vec				p3;
	t_vec				nor;
	t_color				diff_color;
	t_color				spec_color;
}						t_data_tri;

typedef struct			s_light
{
	t_vec				center;
	t_color				color;
	double				ratio;
	double				spec_n;
}						t_light;

typedef struct			s_ro_ras
{
	double				ras_x;
	double				ras_y;
	double				ras_z;
}						t_ro_ras;

typedef struct			s_map_info
{
	double				aspect_ratio;
	int					image_width;
	int					image_height;
	t_vec				orient;
	double				viewport_height;
	double				viewport_width;
	double				focal_length;
	double				fov_horizontal;
	double				t;
	t_vec				origin;
	t_vec				horizontal;
	t_vec				vertical;
	t_vec				p_ll;
	t_vec				p_hl;
	t_vec				p_lr;
	t_vec				p_c;
	t_obj				**objs;
	t_light				**lights;
	t_cam				**cams;
	t_light				ambient;
	t_ro_ras			rotate_info;
	size_t				objs_num;
	size_t				lights_num;
	size_t				l_iter;
	size_t				o_iter;
	size_t				c_iter;
	int					n_c_idx;
	int					screen_x;
	int					screen_y;
	size_t				r_cnt;
	size_t				c_cnt;
	size_t				a_cnt;
}						t_map_info;

typedef struct			s_wins
{
	void				*mlx;
	void				*win;
	t_data				*img;
	t_map_info			*map;
}						t_wins;

# pragma pack(push, 1)

typedef struct			s_bmfh
{
	char				id1;
	char				id2;
	unsigned int		size;
	unsigned short		reserved1;
	unsigned short		reserved2;
	unsigned int		offset;
}						t_bmfh;

typedef struct			s_bmih
{
	unsigned int		size;
	int					width;
	int					height;
	unsigned short		planes;
	unsigned short		bit_count;
	unsigned int		compression;
	unsigned int		bit_size;
	int					x_pels_per_meter;
	int					y_pels_per_meter;
	unsigned int		color_used;
	unsigned int		color_important;
}						t_bmih;

typedef struct			s_rgbt
{
	unsigned char		blue;
	unsigned char		green;
	unsigned char		red;
}						t_rgbt;

# pragma pack(pop)

int						get_next_line(int fd, char **line);
char					**ft_split(char *str, char *charset);
char					**ft_split_free(char **target, unsigned int idx);
unsigned int			ft_next(char *str, char *charset,
									unsigned int s, int is_sep);
int						ft_atoi(const char *str);
double					ft_atod(const char *str);
double					vec_length_squared(t_vec a);
double					vec_length(t_vec a);
double					vec_dot(t_vec a, t_vec b);
t_vec					vec_multi(t_vec a, t_vec b);
t_vec					vec_minus(t_vec a, t_vec b);
t_vec					vec_plus(t_vec a, t_vec b);
t_vec					vec_init(double x, double y, double z);
t_vec					vec_to_unit(t_vec a);
void					ft_mlx_pixel_put(t_data *data, int x, int y,
								t_color col);
t_vec					vec_scala_multi(t_vec a, double t);
t_color					color_int_to_col(int r, int g, int b);
t_color					color_dbl_to_col(double r, double g, double b);
int						color_col_to_int(t_color col);
t_color					color_scala_multi(t_color a, double t, t_color clamp);
t_color					color_init(double r, double g, double b);
t_color					color_plus(t_color a, t_color b, t_color clamp);
double					sphere_hit(void *data, t_vec origin, t_vec dir);
t_vec					sphere_get_nor(t_data_sphere *data,
								t_vec origin, t_vec u_dir, double t);
t_vec					ray_at(t_vec origin, t_vec u_dir, double t);
t_shade					sphere_get_colt(t_map_info *map, size_t obj_idx,
								size_t lig_idx, t_vec origin);
double					ray_is_block(t_map_info *map, size_t obj_idx,
								t_vec origin, t_vec u_dir);
t_shade					shade_init(t_color a, double b, double c);
t_shade					shade_plus(t_shade a, t_shade b);
int						ft_puterror(int opt);
int						parse_make_map(t_map_info *map, const char *path);
int						ft_close(int fd, int ret);
size_t					parse_spl_len(char **splited);
char					**ft_split_free(char **target, unsigned int idx);
int						ft_is_double(const char *str);
int						parse_color(char **splited, t_color *col);
int						parse_vec(char **splited, t_vec *vec);
int						parse_cam(t_map_info *map, char **splited);
int						parse_light(t_map_info *map, char **splited);
int						ft_free(void *target, int ret);
int						parse_sphere(t_map_info *m, char **splited);
int						parse_mapper(t_map_info *map, char **splited);
void					map_free(t_map_info *map);
double					ft_to_radian(double input);
double					ft_to_degree(double input);
void					rotate_by_unit(t_map_info *map);
t_vec					rotate_by_x(t_vec origin, double theta_base_x);
t_vec					rotate_by_y(t_vec origin, double theta_base_y);
t_vec					rotate_by_z(t_vec origin, double theta_base_z);
void					make_view_plane(t_map_info *map);
void					*hit_func_mapper(t_map_info *map, size_t idx);
t_color					get_hit_col(t_map_info *map, t_vec unit_dir,
								double t_max, size_t hit_idx);
void					*col_func_mapper(t_map_info *map, size_t idx);
int						parse_plane(t_map_info *m, char **splited);
double					plane_hit(void *data, t_vec origin, t_vec u_dir);
t_shade					plane_get_colt(t_map_info *map, size_t obj_idx,
								size_t lig_idx, t_vec origin);
int						key_press(int keycode, t_wins *map);
int						mouse_exit(t_wins *wins);
t_color					do_loop(t_map_info *map, double u, double v,
								size_t hit_idx);
void					draw_image(t_wins *wins, int i, int j);
void					square_make_data(t_data_square *data);
int						parse_square(t_map_info *m, char **splited);
double					square_hit(void *data, t_vec origin, t_vec u_dir);
t_shade					square_get_colt(t_map_info *map, size_t obj_idx,
								size_t lig_idx, t_vec origin);
int						parse_cylinder(t_map_info *m, char **splited);
int						parse_disk(t_map_info *m, t_data_cylinder *t);
int						ft_free2(void *target, void *target2, int ret);
double					disk_hit(void *data, t_vec origin, t_vec u_dir);
t_shade					disk_get_colt(t_map_info *map, size_t obj_idx,
								size_t lig_idx, t_vec origin);
double					cylinder_hit(void *data, t_vec origin, t_vec u_dir);
t_shade					cylinder_get_colt(t_map_info *map, size_t obj_idx,
								size_t lig_idx, t_vec origin);
double					cylinder_hit_a(t_data_cylinder *data, t_vec origin,
								t_vec u_dir);
double					cylinder_hit_b(t_data_cylinder *data, t_vec origin,
								t_vec u_dir);
double					cylinder_hit_c(t_data_cylinder *data, t_vec origin,
								t_vec u_dir);
t_vec					vec_cross(t_vec a, t_vec b);
int						parse_tri(t_map_info *m, char **splited);
double					tri_hit(void *data, t_vec origin, t_vec u_dir);
t_shade					tri_get_colt(t_map_info *map, size_t obj_idx,
								size_t lig_idx, t_vec origin);
t_bmfh					bmp_get_file_header(t_map_info *m);
t_bmih					bmp_get_info_header(t_map_info *m);
t_rgbt					bmp_get_rgbt_by_color(t_color color);
void					bmp_set_header(t_map_info *m, int fd);
void					bmp_close_and_free(t_map_info *m, int fd);
t_color					color_multi(t_color a, t_color b, t_color clamp);
int						map_checker(t_map_info *map, int opt);
void					make_map_from_cam(t_map_info *map, size_t c_idx);
void					map_init(t_map_info *map);
int						rt_checker(char *str);

#endif
