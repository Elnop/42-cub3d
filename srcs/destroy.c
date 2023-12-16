/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   destroy.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lperroti <lperroti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/29 18:32:06 by lperroti          #+#    #+#             */
/*   Updated: 2023/12/16 00:30:34 by lperroti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int	destroy_and_exit(t_app *papp)
{
	mlx_destroy_window(papp->mlx, papp->win);
	image_delete(papp->mlx, papp->texea.img);
	image_delete(papp->mlx, papp->texso.img);
	image_delete(papp->mlx, papp->texno.img);
	image_delete(papp->mlx, papp->texwe.img);
	mlx_destroy_display(papp->mlx);
	free(papp->mlx);
	array_free(papp->map);
	exit(0);
	return (1);
}
