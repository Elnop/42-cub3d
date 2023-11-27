/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lperroti <lperroti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/27 19:01:40 by lperroti          #+#    #+#             */
/*   Updated: 2023/11/27 19:01:44 by lperroti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# define XK_MISCELLANY
# define XK_LATIN1
# include "../libs/minilibx-linux/mlx.h"
# include <X11/keysymdef.h>
# include <math.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <fcntl.h>

# include "../libs/liblp_c/liblp.h"

# define WINDOW_HEIGHT 700
# define WINDOW_WIDTH 700

# define HELPER "./cub3d <map file>\n"

typedef struct s_app {
	t_array	map;
}	t_app;

#endif