/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   line.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fvon-der <fvon-der@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/06 14:10:11 by fvon-der          #+#    #+#             */
/*   Updated: 2025/02/27 08:05:35 by fvon-der         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static void	draw_vertical_line(t_renderer *renderer, t_map *map, int x, int y);
static void	draw_horizontal_line(t_renderer *renderer,
				t_map *map, int x, int y);

int	draw_line(t_renderer *renderer, t_point *start, t_point *end)
{
	bresenham_draw(renderer, start, end);
	return (EXIT_SUCCESS);
}

int	init_line_params(t_point start, t_point end,
			t_point *delta, t_point *sign)
{
	delta->x = abs(end.x - start.x);
	delta->y = abs(end.y - start.y);
	if (start.x < end.x)
		sign->x = 1;
	else
		sign->x = -1;
	if (start.y < end.y)
		sign->y = 1;
	else
		sign->y = -1;
	return (EXIT_SUCCESS);
}

static void	draw_horizontal_line(t_renderer *renderer, t_map *map, int x, int y)
{
	t_point	start;
	t_point	end;

	start = project_point(renderer, x, y, map->grid[y][x]);
	start.color = renderer->map->color[y][x];
	if (x < map->width - 1)
	{
		end = project_point(renderer, x + 1, y, map->grid[y][x + 1]);
		end.color = renderer->map->color[y][x + 1];
		if ((start.x < 0 || start.x >= renderer->win_width || start.y < 0
				|| start.y >= renderer->win_height)
			&& (end.x < 0 || end.x >= renderer->win_width
				|| end.y < 0 || end.y >= renderer->win_height))
		{
			return ;
		}
		draw_line(renderer, &start, &end);
	}
}

static void	draw_vertical_line(t_renderer *renderer, t_map *map, int x, int y)
{
	t_point	start;
	t_point	end;

	start = project_point(renderer, x, y, map->grid[y][x]);
	start.color = renderer->map->color[y][x];
	if (y < map->height - 1)
	{
		end = project_point(renderer, x, y + 1, map->grid[y + 1][x]);
		end.color = renderer->map->color[y + 1][x];
		if ((start.x < 0 || start.x >= renderer->win_width
				|| start.y < 0 || start.y >= renderer->win_height)
			&& (end.x < 0 || end.x >= renderer->win_width
				|| end.y < 0 || end.y >= renderer->win_height))
		{
			return ;
		}
		draw_line(renderer, &start, &end);
	}
}

int	draw_map_line(t_renderer *renderer, t_map *map)
{
	int	x;
	int	y;

	y = 0;
	while (y < map->height)
	{
		x = 0;
		while (x < map->width)
		{
			draw_horizontal_line(renderer, map, x, y);
			draw_vertical_line(renderer, map, x, y);
			x++;
		}
		y++;
	}
	return (EXIT_SUCCESS);
}
