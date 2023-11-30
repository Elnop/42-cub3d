/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lperroti <lperroti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/27 13:15:22 by lperroti          #+#    #+#             */
/*   Updated: 2023/11/30 01:26:14 by lperroti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"


void	draw_game(t_app *papp)
{
	t_image	win_img;

	win_img = image_new(papp->mlx, papp->win_w, papp->win_h);
	draw_minimap(papp, win_img);
	mlx_put_image_to_window(papp->mlx, papp->win, win_img.img, 0, 0);
}

int	main(int ac, char **av)
{
	t_app	app;

	if (!init(ac, av, &app))
	{
		lp_dprintf(2, HELPER);
		return (1);
	}
	draw_game(&app);
	mlx_loop(app.mlx);
	return (0);
}
