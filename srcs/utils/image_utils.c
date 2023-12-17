/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   image_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lperroti <lperroti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/29 18:23:37 by lperroti          #+#    #+#             */
/*   Updated: 2023/12/17 03:54:01 by lperroti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

t_image	image_new(void *mlx, size_t width, size_t height)
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

t_texture	load_tex(void *mlx, char *fn)
{
	t_texture	tex;

	if (!fn)
		return (lp_printf("can't load null texture\n"), (t_texture){});
	tex.img.img = mlx_xpm_file_to_image(mlx, fn, &tex.w, &tex.h);
	if (!tex.img.img)
		return (lp_printf("'%s' file not found\n", fn), free(fn), (t_texture){});
	tex.img.addr = mlx_get_data_addr(
			tex.img.img,
			&tex.img.bits_per_pixel,
			&tex.img.line_length,
			&tex.img.endian
			);
	return (free(fn), tex);
}

void	image_delete(void	*mlx, t_image img)
{
	if (img.img)
		mlx_destroy_image(mlx, img.img);
	img = (t_image){};
}

void	image_put_px(t_image img, int x, int y, int color)
{
	if (y < 0 || x < 0 || y > WIN_H || x > WIN_W)
		return ;
	img.addr += (y * img.line_length + x * (img.bits_per_pixel / 8));
	*(int *)img.addr = color;
}

int	image_get_px_color(t_image img, int x, int y)
{
	img.addr += (y * img.line_length + x * (img.bits_per_pixel / 8));
	return (*(int *)img.addr);
}
