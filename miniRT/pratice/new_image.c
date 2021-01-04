/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   new_image.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: honlee <honlee@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/03 23:40:01 by honlee            #+#    #+#             */
/*   Updated: 2021/01/04 00:10:32 by honlee           ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include <mlx.h>

typedef struct	s_data
{
	void		*img;
	char		*addr;
	int			bits_per_pixel;
	int			line_length;
	int			endian;
}				t_data;

void	my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
	char		*dst;
	int			offset;

	offset = (y * data->line_length + x * (data->bits_per_pixel / 8));
	dst = data->addr + offset;
	*(unsigned int *)dst = color;
}

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