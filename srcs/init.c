/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lperroti <lperroti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/29 18:00:46 by lperroti          #+#    #+#             */
/*   Updated: 2023/11/29 18:01:08 by lperroti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

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

void	print_str_array(t_array arr)
{
	size_t	i;

	i = 0;
	while (i < array_size(arr))
		lp_putendl_fd(((char **)arr)[i++], 2);
}

bool	flood_fill(char **map, size_t x, size_t y)
{
	if (!y || !x || y + 1 == array_size(map) || x + 1 == ft_strlen(map[y]))
		return (false);
	map = array_dup(map);
	map[y][x] = '1';
	// print_str_array(map);
	// lp_putchar_fd('\n', 2);
	if (!map)
		return ((void)lp_printf("flood_fill array_dup call error"), false);
	if (map[y][x + 1] != '1' && !flood_fill(map, x + 1, y))
		return (false);
	if (map[y][x - 1] != '1' && !flood_fill(map, x - 1, y))
		return (false);
	if (map[y + 1][x] != '1' && !flood_fill(map, x, y + 1))
		return (false);
	if (map[y - 1][x] != '1' && !flood_fill(map, x, y - 1))
		return (false);
	return (true);
}

bool	check_map(t_array map)
{
	size_t	p_x;
	size_t	p_y;

	p_y = 0;
	p_x = 0;
	while (p_y < array_size(map))
	{
		if (lp_strchr(((char **)map)[p_y], 'N'))
		{
			p_x = lp_strchr(((char **)map)[p_y], 'N') - ((char **)map)[p_y];
			break ;
		}
		p_y++;
	}
	if (!p_x || !flood_fill(map, p_x, p_y))
		return (false);
	return (true);
}

bool	init(int ac, char **av, t_app *papp)
{
	int	map_fd;

	if (ac < 2 || !av[1][0])
		return (false);
	map_fd = open(av[1], O_RDONLY);
	papp->map = read_map(map_fd);
	if (!papp->map || !check_map(papp->map))
	{
		lp_dprintf(2, "BAD MAP\n");
		return (false);
	}
	return (true);
}