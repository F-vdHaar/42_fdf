/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fvon-de <fvon-der@student.42heilbronn.d    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/03 14:13:19 by fvon-de           #+#    #+#             */
/*   Updated: 2025/02/23 12:27:52 by fvon-de          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	get_color(t_map *map, int x, int y)
{
	int		z;
	double	t;

	z = map->color[x][y];
	if (map->z_max == map->z_min)
		return (0xFFFFFF);
	t = (z - map->z_min) / (double)(map->z_max - map->z_min);
	return (i_color(0x0000FF, 0xFF0000, t));
}

int	i_color(int color1, int color2, double t)
{
	int	r;
	int	g;
	int	b;

	r = (int)((1 - t) * ((color1 >> 16) & 0xFF) + t * ((color2 >> 16) & 0xFF));
	g = (int)((1 - t) * ((color1 >> 8) & 0xFF) + t * ((color2 >> 8) & 0xFF));
	b = (int)((1 - t) * (color1 & 0xFF) + t * (color2 & 0xFF));
	return ((r << 16) | (g << 8) | b);
}
