/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lperroti <lperroti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/27 13:15:22 by lperroti          #+#    #+#             */
/*   Updated: 2023/11/27 20:38:40 by lperroti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"
#include <stddef.h>

t_array	read_map(int map_fd)
{
	t_array	map;
	char	*line;

	map = array_new(1, sizeof(char *), array_str_copy, array_str_destroy);
	line = get_next_line(map_fd);
	while (line)
	{
		if (!array_pushback(&map, &line))
			return (array_free(map), NULL);
	}
	return (map);
}

bool	flood_fill(t_array map, size_t p_x, size_t p_y)
{
	
}

bool	check_map(t_array map)
{
	size_t	p_x;
	size_t	p_y;

	p_y = 0;
	while (p_y < array_size(map))
	{
		if (lp_strchr(((char **)map)[p_y], 'N'))
		{
			p_x = lp_strchr(((char **)map)[p_y], 'N') - ((char **)map)[p_y];
			break ;
		}
	}
	flood_fill(map,  p_x, p_y);
}

bool	init(int ac, char **av, t_app *papp)
{
	int	map_fd;

	if (ac < 2 || !av[1][0])
		return (false);
	map_fd = open(av[1], O_RDONLY);
	papp->map = read_map(map_fd);
	if (!papp->map || !check_map(array_dup(papp->map)))
	{
		lp_dprintf(2, "BAD MAP\n");
		return (false);
	}
}

int	main(int ac, char **av)
{
	t_app	app;

	if (!init(ac, av, &app))
	{
		lp_dprintf(2, HELPER);
		return (1);
	}
	return (0);
}
