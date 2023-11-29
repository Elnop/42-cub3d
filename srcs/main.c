/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lperroti <lperroti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/27 13:15:22 by lperroti          #+#    #+#             */
/*   Updated: 2023/11/29 20:27:00 by lperroti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"
#include <stddef.h>

int	main(int ac, char **av)
{
	t_app	app;

	if (!init(ac, av, &app))
	{
		lp_dprintf(2, HELPER);
		return (1);
	}
	//draw_minimap(&app);
	return (0);
}
