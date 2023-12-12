/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   image_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lperroti <lperroti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/29 18:23:37 by lperroti          #+#    #+#             */
/*   Updated: 2023/12/12 03:35:12 by lperroti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

t_image	image_new(void	*mlx, size_t width, size_t height)
{
	t_image	img;

	img.img = mlx_new_image(mlx, width, height);
	if (!img.img)
		return ((t_image){});
	img.addr = mlx_get_data_addr(
			img.img,
			&img.bits_per_pixel,
			&img.line_length,
			&img.endian
			);
	return (img);
}

void	image_delete(void	*mlx, t_image img)
{
	mlx_destroy_image(mlx, img.img);
	img = (t_image){};
}

void	image_put_px(t_image img, int x, int y, int color)
{
	if (x < 0 || y < 0 || x > WIN_WIDTH || y > WIN_H)
		return ;
	img.addr += (y * img.line_length + x * (img.bits_per_pixel / 8));
	*(int *)img.addr = color;
}

int	image_get_px_color(t_image img, int x, int y)
{
	img.addr += (y * img.line_length + x * (img.bits_per_pixel / 8));
	return (*(int *)img.addr);
}
