/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   renderer.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fvon-der <fvon-der@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/02 15:10:42 by fvon-de           #+#    #+#             */
/*   Updated: 2025/02/27 07:39:49 by fvon-der         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	init_image(t_renderer *renderer);

int	put_pixel(t_renderer *renderer, int x, int y, int color)
{
	int	pixel_index;

	if (x >= 0 && x < renderer->win_width && y >= 0 && y < renderer->win_height)
	{
		pixel_index = (y * renderer->win_width + x) * 4;
		if (pixel_index + 3 < renderer->mlx->width * renderer->mlx->height * 4)
		{
			renderer->image->pixels[pixel_index + 0] = (color >> 24) & 0xFF;
			renderer->image->pixels[pixel_index + 1] = (color >> 16) & 0xFF;
			renderer->image->pixels[pixel_index + 2] = (color >> 8) & 0xFF;
			renderer->image->pixels[pixel_index + 3] = color & 0xFF;
		}
	}
	return (EXIT_SUCCESS);
}

int	init_renderer(t_renderer *renderer)
{
	renderer->win_width = 800;
	renderer->win_height = 600;
	renderer->is_focused = 1;
	renderer->keymode = 0;
	renderer->mlx = mlx_init(renderer->win_width,
			renderer->win_height, "FDF", 0);
	if (!renderer->mlx->window)
	{
		log_error("Error: Failed to initialize MLX");
		return (EXIT_FAILURE);
	}
	renderer->image = mlx_new_image(renderer->mlx,
			renderer->win_width, renderer->win_height);
	if (!renderer->image)
	{
		log_error("Error: Failed to create image");
		mlx_terminate(renderer->mlx);
		return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}

int	render_map(t_renderer *renderer)
{
	int	x;
	int	y;

	y = -1;
	while (++y < renderer->map->height)
	{
		x = -1;
		while (++x < renderer->map->width)
		{
			draw_map_line(renderer, renderer->map);
		}
	}
	return (EXIT_SUCCESS);
}
