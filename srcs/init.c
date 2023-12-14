/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lperroti <lperroti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/29 18:00:46 by lperroti          #+#    #+#             */
/*   Updated: 2023/12/14 22:50:44 by lperroti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

bool	init_player(t_app *papp)
{
	float	y;

	y = 0;
	while (y < array_size(papp->map))
	{
		if (lp_strchr(((char **)papp->map)[(int)y], 'N'))
			return (set_player(papp,
					lp_strchr(((char **)papp->map)[(int)y], 'N')
				- ((char **)papp->map)[(int)y], y, 'N'));
		if (lp_strchr(((char **)papp->map)[(int)y], 'O'))
			return (set_player(papp,
					lp_strchr(((char **)papp->map)[(int)y], 'O')
				- ((char **)papp->map)[(int)y], y, 'O'));
		if (lp_strchr(((char **)papp->map)[(int)y], 'W'))
			return (set_player(papp,
					lp_strchr(((char **)papp->map)[(int)y], 'W')
				- ((char **)papp->map)[(int)y], y, 'W'));
		if (lp_strchr(((char **)papp->map)[(int)y], 'S'))
			return (set_player(papp,
					lp_strchr(((char **)papp->map)[(int)y], 'S')
				- ((char **)papp->map)[(int)y], y, 'S'));
		y++;
	}
	return (false);
}

bool	set_player(t_app *papp, float x, float y, char cardinal)
{
	((char **)papp->map)[(int)y][(int)x] = '0';
	papp->p.x = x;
	papp->p.y = y;
	if (cardinal == 'N')
		papp->p_dir = -M_PI / 2;
	if (cardinal == 'S')
		papp->p_dir = M_PI / 2;
	if (cardinal == 'E')
		papp->p_dir = 0;
	if (cardinal == 'W')
		papp->p_dir = -M_PI;
	return (!init_player(papp));
}

void	init_minimap(t_app *papp)
{
		papp->mini_map_h = (float)papp->win_h * MAP_SIZE;
		papp->mini_map_w = (float)papp->win_w * MAP_SIZE;
		papp->tile_h
		= ceil((float)papp->mini_map_h / array_size(((char **)papp->map)));
		papp->tile_w
		= ceil((float)papp->mini_map_w / lp_strlen(((char **)papp->map)[0]));
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
	papp->p = (t_coor){};
	if (!init_player(papp) && lp_dprintf(2, "PLAYER NOT FOUND\n"))
		return (array_free(papp->map), false);
	if (!papp->map || !check_map(papp->map, papp->p))
		return (array_free(papp->map), (void)lp_dprintf(2, "BAD MAP\n"), false);
	if (!init_mlx(papp))
		return (array_free(papp->map), false);
	if (!init_textures(papp, open(av[1], O_RDONLY)))
		return (false);
	if (!papp->win)
		return (array_free(papp->map), free(papp->mlx), false);
	papp->win_h = WIN_H;
	papp->win_w = WIN_W;
	(init_minimap(papp), init_hooks(papp));
	return (true);
}
