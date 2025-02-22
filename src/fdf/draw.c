/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fvon-de <fvon-der@student.42heilbronn.d    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/04 19:18:22 by fvon-der          #+#    #+#             */
/*   Updated: 2025/02/22 07:51:57 by fvon-de          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static double calculate_t(t_point *start, t_point *end, t_point cur);


int	bresenham_draw(t_renderer *renderer, t_point *start, t_point *end)
{
	t_point	delta;
	t_point	sign;
	t_point	cur;
	int		error[2];
	double	t;
	int	color;

	if (!start || !end) 
	{
		ft_printf("ERROR: start or end is NULL!\n");
		return (EXIT_FAILURE);	
	}

	// **Check if both start and end are completely outside the window**
	if ((start->x < 0 || start->x >= renderer->win_width || start->y < 0 || start->y >= renderer->win_height) &&
		(end->x < 0 || end->x >= renderer->win_width || end->y < 0 || end->y >= renderer->win_height))
	{
		ft_printf("WARNING: Line is completely outside the window, skipping drawing.\n");
		return (EXIT_SUCCESS);
	}

/* 	//ft_printf("DEBUG: [bresenham_draw] Start drawing \n from x = %i, y = %i, color = %i\n to x = %i, y = %i, color = %i\n",
		(int)start->x, 	(int)start->y, (int)start->color, 
		(int)end->x, (int)end->y, (int)(end->color)) ; */

	init_line_params(*start, *end, &delta, &sign);
	error[0] = delta.x - delta.y;
	cur = *start;

	while (cur.x != end->x || cur.y != end->y)
	{
		// **Only draw if the current point is inside the window boundaries**
		if (cur.x >= 0 && cur.x < renderer->win_width && cur.y >= 0 && cur.y < renderer->win_height)
		{
			t = calculate_t(start, end, cur);
			color = i_color(start->color, end->color, t);
			put_pixel(renderer, cur.x, cur.y, color);
		}

		error[1] = 2 * error[0];

		if (error[1] > -delta.y)
		{
			error[0] -= delta.y;
			cur.x += sign.x;
		}
		if (error[1] < delta.x)
		{
			error[0] += delta.x;
			cur.y += sign.y;
		}
	}

	//ft_printf("DEBUG: [bresenham_draw] Finished drawing the line\n");
	//mlx_put_image_to_window(renderer->mlx.mlx_ptr, renderer->mlx.win_ptr, renderer->mlx.img_ptr, 0, 0);
    return (EXIT_SUCCESS);
}

static double calculate_t(t_point *start, t_point *end, t_point cur)
{
    int dx;
    int dy;
    int line_length;
    int cur_length;

    dx = abs(end->x - start->x);
    dy = abs(end->y - start->y);
    line_length = dx;
    if (dy > dx)
        line_length = dy;
    cur_length = abs(cur.x - start->x);
    if (abs(cur.y - start->y) > cur_length)
        cur_length = abs(cur.y - start->y);
    if (line_length == 0)
        return (0.0); // Return 0.0 as a double
    return ((double)cur_length / (double)line_length); // Return a double between 0.0 and 1.0
}
int	render_map(t_renderer *renderer)
{
	int	x;
	int	y;


	y = -1;
	while (++y < renderer->map->height)
	{
		//ft_printf("DEBUG: [render_map] Rendering row %d (y = %d)\n", y, y);
		x = -1;
		while (++x < renderer->map->width)
		{
/* 			//ft_printf("DEBUG: [render_map] Rendering column %d (x = %d), grid value = %d\n",
				x, x, renderer->map->grid[y][x]); */
			draw_map_line(renderer, renderer->map);
		}
	}
/* 
	//ft_printf("DEBUG: [render_map] Map rendering completed, rows: %d, columns: %d\n", 
		renderer->map->height, renderer->map->width); */
    return (EXIT_SUCCESS);
}
