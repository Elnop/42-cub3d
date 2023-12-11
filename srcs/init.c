/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lperroti <lperroti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/29 18:00:46 by lperroti          #+#    #+#             */
/*   Updated: 2023/12/11 21:30:31 by lperroti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"
#include <math.h>
#include <stdio.h>

t_array	read_map(int map_fd)
{
	t_array	map;
	char	*l;
	char	*tmp;

	map = array_new(1, sizeof(char *), array_str_copy, array_str_destroy);
	l = get_next_line(map_fd);
	while (l)
	{
		if (l[lp_strlen(l) - 1] == '\n')
		{
			tmp = lp_substr(l, 0, lp_strlen(l) - 1);
			free(l);
			l = tmp;
		}
		if (!array_pushback(&map, &l))
			return (array_free(map), NULL);
		free(l);
		l = get_next_line(map_fd);
	}
	free(l);
	return (map);
}

bool	set_player(t_app *papp, float x, float y, char cardinal)
{
	if (papp->p.x)
		return (false);
	((char **)papp->map)[(int)y][(int)x] = '0';
	papp->p.x = x;
	papp->p.y = y;
	if (cardinal == 'N')
		papp->p_dir = - M_PI / 2;
	if (cardinal == 'S')
		papp->p_dir = M_PI / 2;
	if (cardinal == 'E')
		papp->p_dir = 0;
	if (cardinal == 'W')
		papp->p_dir = - M_PI;
	return (true);
}

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

void	init_minimap(t_app *papp)
{
		papp->mini_map_h = (float)papp->win_h * MAP_SIZE;
		papp->mini_map_w = (float)papp->win_w * MAP_SIZE;
		papp->tile_h
		= ceil((float)papp->mini_map_h / array_size(((char **)papp->map)));
		papp->tile_w
		= ceil((float)papp->mini_map_w / lp_strlen(((char **)papp->map)[0]));
}

bool	init(int ac, char **av, t_app *papp)
{
	int	map_fd;

	if (ac < 2 || !av[1][0])
		return (false);
	map_fd = open(av[1], O_RDONLY);
	if (map_fd == -1)
		return (false);
	papp->map = read_map(map_fd);
	close(map_fd);
	papp->p = (t_coor){};
	if (!init_player(papp) && lp_dprintf(2, "PLAYER NOT FOUND\n"))
		return (array_free(papp->map), false);
	if (!papp->map || !check_map(papp->map, papp->p))
		return (array_free(papp->map), (void)lp_dprintf(2, "BAD MAP\n"), false);
	papp->mlx = mlx_init();
	if (!papp->mlx)
		return (array_free(papp->map), false);
	papp->win = mlx_new_window(papp->mlx, WIN_WIDTH, WIN_HEIGHT, "cub3d");
	if (!papp->win)
		return (array_free(papp->map), free(papp->mlx), false);
	papp->win_h = WIN_HEIGHT;
	papp->win_w = WIN_WIDTH;
	init_minimap(papp);
	init_hooks(papp);
	return (true);
}
