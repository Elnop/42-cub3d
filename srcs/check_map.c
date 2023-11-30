/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lperroti <lperroti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/30 17:46:08 by lperroti          #+#    #+#             */
/*   Updated: 2023/11/30 18:11:28 by lperroti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

bool	flood_fill(char **map, size_t x, size_t y)
{
	if (!y || !x || y + 1 == array_size(map) || x + 1 == ft_strlen(map[y])
		|| map[y][x] == ' ')
		return (false);
	map[y][x] = '1';
	if (!map)
		return ((void)lp_printf("flood_fill array_dup call error"), false);
	if (map[y + 1][x] != '1' && !flood_fill(map, x, y + 1))
		return (false);
	if (map[y][x + 1] != '1' && !flood_fill(map, x + 1, y))
		return (false);
	if (map[y][x - 1] != '1' && !flood_fill(map, x - 1, y))
		return (false);
	if (map[y - 1][x] != '1' && !flood_fill(map, x, y - 1))
		return (false);
	return (true);
}

bool	check_map(t_array map, t_coordinates player)
{
	size_t			x;
	size_t			y;
	t_array			flooded_map;

	flooded_map = array_dup(map);
	if (!flooded_map || !flood_fill(flooded_map, player.x, player.y))
		return (array_free(flooded_map), false);
	y = 0;
	while (y < array_size(flooded_map))
	{
		x = 0;
		while (x < lp_strlen(((char **)flooded_map)[y]))
		{
			if (((char **)flooded_map)[y][x] == '0')
				return (array_free(flooded_map), false);
			x++;
		}
		y++;
	}
	return (array_free(flooded_map), true);
}