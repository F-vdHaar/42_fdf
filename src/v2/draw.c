/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fvon-de <fvon-der@student.42heilbronn.d    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/09 07:49:41 by fvon-de           #+#    #+#             */
/*   Updated: 2025/03/12 13:45:19 by fvon-de          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static void	bresenham(mlx_image_t *image, t_point a, t_point b)
{
	int			error[2];
	t_point		cur;

	cur.x = a.x;
	cur.y = a.y;
	error[0] = abs(b.x - a.x) - abs(b.y - a.y);
	while (cur.x != b.x || cur.y != b.y)
	{
		if ((uint32_t)cur.x < image->width && (uint32_t)cur.y < image->height)
			mlx_put_pixel(image, cur.x, cur.y, get_color(cur, a, b));
		error[1] = 2 * error[0];
		if (error[1] > -abs(b.y - a.y))
		{
			error[0] -= abs(b.y - a.y);
			cur.x += (a.x < b.x);
			cur.x -= (b.x < a.x);
		}
		if (error[1] < abs(b.x - a.x))
		{
			error[0] += abs(b.x - a.x);
			cur.y += (a.y < b.y);
			cur.y -= (b.y < a.y);
		}
	}
}

void	project(t_map *map, int i, int j)
{
	t_point_virt	*previous;
	t_point_virt	temp;
	t_point			*new;

	previous = &(map->grid_virt[i][j]);
	new = &(map->grid[i][j]);
	temp.x = previous->x * map->scale_x;
	temp.y = previous->y * map->scale_y;
	temp.z = previous->z * map->scale_z;
	rotate_z(&temp.x, &temp.y, map->rot_z);
	rotate_x(&temp.y, &temp.z, map->rot_x);
	rotate_y(&temp.x, &temp.z, map->rot_y);
	new->x = (int)((temp.x * map->zoom - temp.y * map->zoom)
			* cos(map->alpha) + map->x_offset);
	new->y = (int)(-temp.z * map->zoom
			+ (temp.x * map->zoom + temp.y * map->zoom)
			* sin(map->beta) + map->y_offset);
	new->col = previous->col;
}

static void	draw_line(t_fdf *fdf, int x, int y)
{
	if (y == 0 && x == 0)
		project(fdf->map, y, x);
	if (y + 1 < fdf->map->rows)
	{
		project(fdf->map, y + 1, x);
		bresenham(fdf->image, fdf->map->grid[y][x],
			fdf->map->grid[y + 1][x]);
	}
	if (x + 1 < fdf->map->cols)
	{
		if (y == 0)
			project(fdf->map, y, x + 1);
		bresenham(fdf->image, fdf->map->grid[y][x],
			fdf->map->grid[y][x + 1]);
	}
}

void	draw_image(void *param)
{
	int		i;
	int		j;
	t_fdf	*fdf;

	fdf = (t_fdf *)param;
	draw_reset(fdf->image);
	i = -1;
	while (++i < fdf->map->rows)
	{
		j = -1;
		while (++j < fdf->map->cols)
			draw_line(fdf, j, i);
	}
}

void	draw_reset(mlx_image_t *image)
{
	size_t	image_size;

	if (image == NULL)
		return ;
	image_size = image->width * image->height * 4;
	memset(image->pixels, 0, image_size);
}
