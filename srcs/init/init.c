/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lperroti <lperroti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/29 18:00:46 by lperroti          #+#    #+#             */
/*   Updated: 2023/12/18 13:54:20 by lperroti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

void	init_minimap(t_app *papp)
{
		papp->mini_map_h = (double)papp->win_h * MAP_SIZE;
		papp->mini_map_w = (double)papp->win_w * MAP_SIZE;
		papp->tile_h
		= ceil((double)papp->mini_map_h / array_size(papp->map));
		papp->tile_w
		= ceil((double)papp->mini_map_w / lp_strlen(papp->map[0]));
}

bool	init_mlx(t_app *papp)
{
	papp->mlx = mlx_init();
	if (!papp->mlx)
		return (false);
	papp->win = mlx_new_window(papp->mlx, WIN_W, WIN_H, "cub3d");
	if (!papp->win)
		return (free(papp->mlx), false);
	return (true);
}

bool	init(int ac, char **av, t_app *papp)
{
	if (ac < 2 || !av[1][0])
		return (false);
	if (!init_map(papp, av[1]))
		return (false);
	papp->p = (t_coo){};
	if (!init_player(papp) && lp_dprintf(2, "PLAYER NOT FOUND\n"))
		return (array_free(papp->map), false);
	if (!papp->map || !check_map(papp->map, papp->p))
		return (array_free(papp->map), (void)lp_dprintf(2, "BAD MAP\n"), false);
	if (!init_mlx(papp))
		return (array_free(papp->map), false);
	if (!init_textures(papp, open(av[1], O_RDONLY)))
		return (destroy_and_exit(papp), false);
	if (!papp->win)
		return (array_free(papp->map), free(papp->mlx), false);
	papp->win_h = WIN_H;
	papp->win_w = WIN_W;
	(init_minimap(papp), init_hooks(papp));
	return (true);
}
