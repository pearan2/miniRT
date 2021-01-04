/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   2.1.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: honlee <honlee@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/03 21:37:36 by honlee            #+#    #+#             */
/*   Updated: 2021/01/04 01:03:55 by honlee           ###   ########seoul.kr  */
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
	int			image_height = (int)((double)400 / aspect_ratio);
	
	mlx_win = mlx_new_window(mlx, image_width, image_height, "Hello 42 Seoul!");
	img.img = mlx_new_image(mlx, image_width, image_height);
	//Camera
	//double		viewport_height = 2.0;
	//double		viewport_width = aspect_ratio * viewport_height;
	//double		focal_length = 1.0;

	//t_vec		origin = vec_init(0, 0, 0);	
	//t_vec		horizontal = vec_init(viewport_width, 0, 0);
	//t_vec		vertical = vec_init(0, viewport_height, 0);
	//t_vec		lower_left_corner = vec_init(-viewport_width/2, -viewport_height/2, -focal_length);

	//Render (make image)
	img.addr = mlx_get_data_addr(img.img, &img.bits_per_pixel, &img.line_length, &img.endian);
	// ex ) my_mlx_pixel_put(&img, 5, 5, 0x00FF0000);
	for (int j = 0; j<image_height; j++)
	{
		for (int i=0; i<image_width; i++)
		{
			double r = (double) i / (double) (image_width - 1);
			double g = (double) j / (double) (image_height - 1);
			double b = 0.25;

			int ir = (int) (255.999 * r);
			int ig = (int) (255.999 * g);
			int ib = (int) (255.999 * b);
			ft_mlx_pixel_put(&img, i, image_height - j, ft_rgb_to_int(ir, ig, ib));
		}
	}
	
	//put image
	mlx_put_image_to_window(mlx, mlx_win, img.img, 0, 0);
	mlx_loop(mlx);	
}