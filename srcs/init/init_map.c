/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lperroti <lperroti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/14 22:39:27 by lperroti          #+#    #+#             */
/*   Updated: 2023/12/17 03:34:55 by lperroti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

static t_array	read_map(int map_fd)
{
	t_array	map;
	char	*l;
	char	*tmp;

	map = array_new(1, sizeof(char *), array_str_copy, array_str_destroy);
	l = get_next_line(map_fd);
	while (l && (lp_isalpha(l[0]) || l[0] == '\n'))
		l = (free(l), get_next_line(map_fd));
	while (l)
	{
		if (l[lp_strlen(l) - 1] == '\n')
		{
			tmp = lp_substr(l, 0, lp_strlen(l) - 1);
			l = (free(l), tmp);
		}
		if (!array_pushback(&map, &l))
			return (array_free(map), NULL);
		l = (free(l), get_next_line(map_fd));
	}
	return (free(l), map);
}

bool	init_map(t_app *papp, char *filename)
{
	int	map_fd;

	map_fd = open(filename, O_RDONLY);
	if (map_fd == -1)
		return (false);
	papp->map = read_map(map_fd);
	close(map_fd);
	return (true);
}
