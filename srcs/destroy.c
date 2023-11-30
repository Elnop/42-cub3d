/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   destroy.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lperroti <lperroti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/29 18:32:06 by lperroti          #+#    #+#             */
/*   Updated: 2023/11/30 18:03:04 by lperroti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int	destroy_app(t_app *papp)
{
	mlx_destroy_window(papp->mlx, papp->win);
	mlx_destroy_display(papp->mlx);
	free(papp->mlx);
	return (1);
}
