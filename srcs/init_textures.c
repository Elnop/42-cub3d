/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_textures.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lperroti <lperroti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/14 22:20:50 by lperroti          #+#    #+#             */
/*   Updated: 2023/12/16 00:33:03 by lperroti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

static t_color	get_rgb(char *str)
{
	t_color	c;

	c.r = lp_atoi(str);
	while (lp_isdigit(*str))
		str++;
	str++;
	c.g = lp_atoi(str);
	while (lp_isdigit(*str))
		str++;
	str++;
	c.b = lp_atoi(str);
	return (c);
}

static void	fcknrm(t_app *papp, char *l)
{
	if (l[0] == 'N' && l[1] == 'O' && l[2] == ' ')
		papp->texno
			= load_tex(papp->mlx, lp_substr(l, 3, lp_strlen(l + 3) - 1));
	if (l[0] == 'S' && l[1] == 'O' && l[2] == ' ')
		papp->texso
			= load_tex(papp->mlx, lp_substr(l, 3, lp_strlen(l + 3) - 1));
	if (l[0] == 'E' && l[1] == 'A' && l[2] == ' ')
		papp->texea
			= load_tex(papp->mlx, lp_substr(l, 3, lp_strlen(l + 3) - 1));
	if (l[0] == 'W' && l[1] == 'E' && l[2] == ' ')
		papp->texwe
			= load_tex(papp->mlx, lp_substr(l, 3, lp_strlen(l + 3) - 1));
	if (l[0] == 'F' && l[1] == ' ')
		papp->floor = get_rgb(l + 2);
	if (l[0] == 'C' && l[1] == ' ')
		papp->ceil = get_rgb(l + 2);
}

bool	init_textures(t_app *papp, int map_fd)
{
	char	*l;

	papp->texno = (t_texture){};
	papp->texso = (t_texture){};
	papp->texea = (t_texture){};
	papp->texwe = (t_texture){};
	l = get_next_line(map_fd);
	while (l && (!lp_isdigit(l[0]) || l[0] != ' ' || l[0] != '\t'))
	{
		fcknrm(papp, l);
		l = (free(l), get_next_line(map_fd));
	}
	close(map_fd);
	if (!papp->texno.w)
		return (lp_printf("CANT LOAD NORD TEXTURE\n"), false);
	if (!papp->texso.w)
		return (lp_printf("CANT LOAD SOUTH TEXTURE\n"), false);
	if (!papp->texwe.w)
		return (lp_printf("CANT LOAD WEAST TEXTURE\n"), false);
	if (!papp->texea.w)
		return (lp_printf("CANT LOAD EAST TEXTURE\n"), false);
	return (true);
}
