/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lperroti <lperroti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/27 19:01:40 by lperroti          #+#    #+#             */
/*   Updated: 2023/11/29 18:31:23 by lperroti         ###   ########.fr       */
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

# define WIN_HEIGHT 700
# define WIN_WIDTH 700

# define HELPER "./cub3d <map file>\n"

typedef struct s_coordinates {
	size_t	x;
	size_t	y;
}	t_coordinates;

typedef struct s_image {
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}	t_image;

typedef union s_color {
	int	hex;
	struct
	{
		char	b;
		char	g;
		char	r;
		char	a;
	};
}	t_color;

typedef struct s_app {
	t_array			map;
	t_coordinates	player;
	void			*mlx;
	void			*win;
}	t_app;

bool	init(int ac, char **av, t_app *papp);

#endif