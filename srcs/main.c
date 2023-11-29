/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lperroti <lperroti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/27 13:15:22 by lperroti          #+#    #+#             */
/*   Updated: 2023/11/29 18:01:18 by lperroti         ###   ########.fr       */
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
	return (0);
}
