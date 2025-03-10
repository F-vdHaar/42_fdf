/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fvon-der <fvon-der@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/08 13:33:25 by fvon-de           #+#    #+#             */
/*   Updated: 2025/03/10 07:23:13 by fvon-der         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

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

int	get_color(t_point current, t_point a, t_point b)
{
	double	t;
	int		dx;
	int		dy;

	if (a.col == b.col)
		return (a.col);
	dx = abs(b.x - a.x);
	dy = abs(b.y - a.y);
	if (dx > dy)
		t = (double)(current.x - a.x) / (b.x - a.x);
	else
		t = (double)(current.y - a.y) / (b.y - a.y);
	return (i_color(a.col, b.col, t));
}
