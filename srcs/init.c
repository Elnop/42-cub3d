/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lperroti <lperroti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/29 18:00:46 by lperroti          #+#    #+#             */
/*   Updated: 2023/11/30 20:11:01 by lperroti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"
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

t_coordinates	get_player_coordinates(char **map)
{
	t_coordinates	player;

	player = (t_coordinates){0, 0};
	while (player.y < array_size(map))
	{
		if (lp_strchr(map[(int)ceil(player.y)], 'N'))
			player.x = lp_strchr(map[(int)ceil(player.y)], 'N') - map[(int)ceil(player.y)];
		if (lp_strchr(map[(int)ceil(player.y)], 'O'))
			player.x = lp_strchr(map[(int)ceil(player.y)], 'O') - map[(int)ceil(player.y)];
		if (lp_strchr(map[(int)ceil(player.y)], 'W'))
			player.x = lp_strchr(map[(int)ceil(player.y)], 'W') - map[(int)ceil(player.y)];
		if (lp_strchr(map[(int)ceil(player.y)], 'S'))
			player.x = lp_strchr(map[(int)ceil(player.y)], 'S') - map[(int)ceil(player.y)];
		if (player.x)
			break ;
		player.y++;
	}
	if (!player.x)
		return ((t_coordinates){});
	((char **)map)[(int)ceil(player.y)][(int)ceil(player.x)] = '0';
	if (get_player_coordinates(map).x)
		return ((t_coordinates){});
	return (player);
}

void	init_minimap(t_app *papp)
{
		papp->mini_map_h = (float)papp->win_h * MAP_SIZE;
		papp->mini_map_w = (float)papp->win_w * MAP_SIZE;
		papp->mini_map_tile_h
		= ceil((double)papp->mini_map_h / array_size(((char **)papp->map)));
		papp->mini_map_tile_w
		= ceil((double)papp->mini_map_w / lp_strlen(((char **)papp->map)[0]));
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
	papp->player = get_player_coordinates(papp->map);
	papp->player_dir = 0;
	if (!papp->player.x && lp_dprintf(2, "PLAYER NOT FOUND\n"))
		return (array_free(papp->map), false);
	if (!papp->map || !check_map(papp->map, papp->player))
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

