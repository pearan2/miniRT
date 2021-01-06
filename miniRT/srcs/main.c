/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: honlee <honlee@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/03 21:37:36 by honlee            #+#    #+#             */
/*   Updated: 2021/01/06 04:44:47 by honlee           ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

int		main()
{
	void		*mlx;
	t_data		img;
	void		*mlx_win;
	t_map_info	map;
	


	//map setting
	//image
	map.apsect_ratio = 16.0 / 9.0;
	map.image_width = 800;
	map.image_height = (int)(map.image_width / map.apsect_ratio);

	//mlx setting
	mlx = mlx_init();	
	mlx_win = mlx_new_window(mlx, map.image_width, map.image_height, "Hello 42 Seoul!");
	img.img = mlx_new_image(mlx, map.image_width, map.image_height);

	//Camera	
	map.viewport_height = 2.0;
	map.viewport_width = map.apsect_ratio * map.viewport_height;
	map.focal_length = 3;

	map.origin = vec_init(0, 0, 0);
	map.horizontal = vec_init(map.viewport_width, 0, 0);
	map.vertical = vec_init(0, map.viewport_height, 0);
	map.lower_left_corner = vec_init(-map.viewport_width/2, -map.viewport_height/2, map.focal_length);

	//obj setting
	map.objs_num = 3;
	map.objs = malloc(sizeof(t_obj *) * map.objs_num);
	//obj[0] data
	t_data_sphere *sp0 = malloc(sizeof(t_data_sphere));
	sp0->center = vec_init(0, -0.5, 5);
	sp0->radius = 0.5;
	sp0->color = color_init(1, 0, 0);

	//obj[1] data
	t_data_sphere *sp1 = malloc(sizeof(t_data_sphere));
	sp1->center = vec_init(0, -101, 5);
	sp1->radius = 100;
	sp1->color = color_init(0.1, 0.9, 0.1);

	t_data_sphere *sp2 = malloc(sizeof(t_data_sphere));
	sp2->center = vec_init(1.05, -0.5, 5);
	sp2->radius = 0.5;
	sp2->color = color_init(0 ,0 ,1);

	map.objs[0] = malloc(sizeof(t_obj));
	map.objs[0]->type = sphere;
	map.objs[0]->data = sp0;

	map.objs[1] = malloc(sizeof(t_obj));
	map.objs[1]->type = sphere;
	map.objs[1]->data = sp1;

	map.objs[2] = malloc(sizeof(t_obj));
	map.objs[2]->type = sphere;
	map.objs[2]->data = sp2;
	//light setting
	map.lights_num = 2;
	map.lights = malloc(sizeof(t_light *) * map.lights_num);
	map.lights[0] = malloc(sizeof(t_light));
	map.lights[0]->color = color_init(1,1,1);
	map.lights[0]->center = vec_init(-5, 5, 5);
	map.lights[0]->lux = 1;

	map.lights[1] = malloc(sizeof(t_light));
	map.lights[1]->color = color_init(1, 1, 1);
	map.lights[1]->center = vec_init(5, 5, 5);
	map.lights[1]->lux = 1;

	//Render (make image)
	img.addr = mlx_get_data_addr(img.img, &img.bits_per_pixel, &img.line_length, &img.endian);
	//ft_mlx_pixel_put(&img, i, image_height - j, ft_rgb_to_int(ir, ig, ib));
	for (int j = map.image_height; j>=0; j--)
	{
		for (int i = 0; i<map.image_width; i++)
		{
			double u = (double) i / (double) (map.image_width);
			double v = (double) j / (double) (map.image_height);
		
			//gradation background
			t_vec dir = vec_plus(map.lower_left_corner, vec_scala_multi(map.horizontal, u));
			dir = vec_plus(dir, vec_scala_multi(map.vertical, v));
			dir = vec_minus(dir, map.origin);
	
			t_vec unit_dir = vec_to_unit(dir);
			
			double t = 0.5 * (unit_dir.y + 1.0);
			t_color pixel_color = color_scala_multi(color_init(1.0, 1.0, 1.0), (1.0 - t));
			t_color pixel_color2 = color_scala_multi(color_init(0.5, 0.7, 1.0), t);
			pixel_color = color_plus(pixel_color, pixel_color2);
			//end of gradation

			size_t	idx = 0;
			//draw hittable obj
			double t_max = DBL_MAX;
			size_t	hit_idx;
			while (idx < map.objs_num)
			{
				double t = sphere_hit(map.objs[idx]->data, map.origin, unit_dir);
				if (t != -1.0)
				{
					if (t < t_max)
					{
						t_max = t;
						hit_idx = idx;
					}
				}
				idx++;
			}
			if (t_max != DBL_MAX)
			{
				idx = 0;
				double t = 0;
				t_vec ori = ray_at(map.origin, unit_dir, t_max);
				while (idx < map.lights_num)
				{
					t += sphere_get_colt(&map, hit_idx, idx, ori);
					idx++;
				}
				pixel_color = ((t_data_sphere *)map.objs[hit_idx]->data)->color;
				pixel_color = color_scala_multi(pixel_color, t);
			}
			//draw
			ft_mlx_pixel_put(&img, i, map.image_height - j, pixel_color);
			// if (i % 50 == 0 && j % 50 == 0)
			// {
			// 	printf("%d, %d\n", i, j);
			// 	printf("%f\n", unit_dir.x);
			// 	printf("%f\n", unit_dir.y);
			// 	printf("%f\n", unit_dir.z);
			// 	printf("-----------------------\n");
			// }
		}
	}
	
	//put image
	mlx_put_image_to_window(mlx, mlx_win, img.img, 0, 0);
	mlx_loop(mlx);	
}