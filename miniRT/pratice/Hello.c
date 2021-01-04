/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Hello.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: honlee <honlee@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/03 23:32:54 by honlee            #+#    #+#             */
/*   Updated: 2021/01/04 00:10:29 by honlee           ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include <mlx.h>

int		main(void)
{
	void		*mlx;
	t_data		img;
	void		*mlx_win;

	mlx = mlx_init();
	mlx_win = mlx_new_window(mlx, 1920, 1080, "Hello 42 Seoul!");
	img.img = mlx_new_image(mlx, 1920, 1080);

	//After creating an image, we can call 'mlx_get_data_addr', we pass
	//'bigs_per_pixel', 'line_length', and 'endian' by reference. These will then be set accordingly 
	//for the *current* data address
	img.addr = mlx_get_data_addr(img.img, &img.bits_per_pixel, &img.line_length, &img.endian);
	my_mlx_pixel_put(&img, 5, 5, 0x00FF0000);
	mlx_put_image_to_window(mlx, mlx_win, img.img, 0, 0);
	mlx_loop(mlx);
}