/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   image_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lperroti <lperroti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/29 18:23:37 by lperroti          #+#    #+#             */
/*   Updated: 2023/11/29 20:26:34 by lperroti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"
#include <stddef.h>

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

void	put_image(t_image img, int x, int y, int color)
{
	img.addr += (y * img.line_length + x * (img.bits_per_pixel / 8));
	*(int *)img.addr = color;
}

int	image_getcolor(t_image img, int x, int y)
{
	img.addr += (y * img.line_length + x * (img.bits_per_pixel / 8));
	return (*(int *)img.addr);
}
