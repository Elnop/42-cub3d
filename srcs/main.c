/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lperroti <lperroti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/27 13:15:22 by lperroti          #+#    #+#             */
/*   Updated: 2023/12/14 23:11:09 by lperroti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int	draw_game(t_app *papp)
{
	t_image	win_img;

	win_img = image_new(papp->mlx, papp->win_w, papp->win_h);
	draw_rect(win_img, (t_coor){0, 0},
		(t_coor){WIN_W, (double)WIN_H / 2}, papp->ceil.hex);
	draw_rect(win_img, (t_coor){0, (double)WIN_H / 2},
		(t_coor){WIN_W, (double)WIN_H / 2}, papp->floor.hex);
	draw_walls(papp, win_img);
	draw_minimap(papp, win_img);
	mlx_put_image_to_window(papp->mlx, papp->win, win_img.img, 0, 0);
	image_delete(papp->mlx, win_img);
	return (0);
}

int	main(int ac, char **av)
{
	t_app	app;

	if (!init(ac, av, &app))
	{
		lp_dprintf(2, HELPER);
		return (1);
	}
	mlx_loop_hook(app.mlx, draw_game, &app);
	mlx_loop(app.mlx);
	return (0);
}
