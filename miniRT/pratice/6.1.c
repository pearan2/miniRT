/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   6.1.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: honlee <honlee@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/03 21:37:36 by honlee            #+#    #+#             */
/*   Updated: 2021/01/05 20:38:04 by honlee           ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"



int		main()
{
	void		*mlx;
	t_data		img;
	void		*mlx_win;

	mlx = mlx_init();


	//Image
	double		aspect_ratio = 16.0 / 9.0;
	int			image_width = 400;
	int			image_height = (int)(image_width / aspect_ratio);
	
	mlx_win = mlx_new_window(mlx, image_width, image_height, "Hello 42 Seoul!");
	img.img = mlx_new_image(mlx, image_width, image_height);
	//Camera
	double		viewport_height = 2.0;
	double		viewport_width = aspect_ratio * viewport_height;
	double		focal_length = 1.0;

	t_vec		origin = vec_init(0, 0, 0);	
	t_vec		horizontal = vec_init(viewport_width, 0, 0);
	t_vec		vertical = vec_init(0, viewport_height, 0);
	t_vec		lower_left_corner = vec_init(-viewport_width/2, -viewport_height/2, focal_length);

	//Render (make image)
	img.addr = mlx_get_data_addr(img.img, &img.bits_per_pixel, &img.line_length, &img.endian);
	//ft_mlx_pixel_put(&img, i, image_height - j, ft_rgb_to_int(ir, ig, ib));
	for (int j = 0; j<image_height; j++)
	{
		for (int i=0; i<image_width; i++)
		{
			double u = (double) i / (double) (image_width - 1);
			double v = (double) j / (double) (image_height - 1);
		
			t_vec dir = vec_plus(lower_left_corner, vec_scala_multi(horizontal, u));
			dir = vec_plus(dir, vec_scala_multi(vertical, v));
			dir = vec_minus(dir, origin);
		
			t_vec unit_dir = vec_to_unit(dir);
			
			double t = 0.5 * (unit_dir.y + 1.0);
			t_color pixel_color = color_scala_multi(color_init(1.0, 1.0, 1.0), (1.0 - t));
			t_color pixel_color2 = color_scala_multi(color_init(0.5, 0.7, 1.0), t);
			pixel_color = color_plus(pixel_color, pixel_color2);

			double hit_t = sphere_hit(vec_init(0, 0, 1), 0.5, origin, dir);
			if (hit_t > 0.0)
			{
				t_vec N = vec_plus(origin, vec_scala_multi(dir, hit_t));
				N = vec_minus(N, vec_init(0, 0, 1));
				N = vec_to_unit(N);
				pixel_color = color_scala_multi(color_init(N.x + 1.0, N.y + 1.0, N.z + 1.0), 0.5);
			}
			ft_mlx_pixel_put(&img, i, image_height - j, pixel_color);
		}
	}
	
	//put image
	mlx_put_image_to_window(mlx, mlx_win, img.img, 0, 0);
	mlx_loop(mlx);	
}