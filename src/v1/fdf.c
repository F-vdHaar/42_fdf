/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fvon-der <fvon-der@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/28 15:21:33 by fvon-der          #+#    #+#             */
/*   Updated: 2025/02/27 07:34:56 by fvon-der         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	main(int argc, char **argv)
{
	t_renderer	*renderer;

	renderer = NULL;
	if (argc != 2)
	{
		ft_printf("Usage: %s <map_file>\n", argv[0]);
		return (EXIT_FAILURE);
	}
	renderer = malloc(sizeof(t_renderer));
	if (!renderer)
	{
		log_error("Error: Failed to allocate memory for renderer");
		return (EXIT_FAILURE);
	}
	ft_memset(renderer, 0, sizeof(t_renderer));
	renderer->need_redraw = 1;
	if (initialize(renderer, argv[1]) == EXIT_FAILURE)
		return (free(renderer), EXIT_FAILURE);
	draw_window(renderer);
	mlx_loop(renderer->mlx);
	cleanup(renderer);
	renderer = NULL;
	return (EXIT_SUCCESS);
}

int	initialize(t_renderer *renderer, char *filename)
{
	renderer->map = malloc(sizeof(t_map));
	renderer->camera = malloc(sizeof(t_camera));
	if (!renderer->map || !renderer->camera)
	{
		log_error("Error: Failed to allocate memory for map or camera");
		cleanup(renderer);
		return (EXIT_FAILURE);
	}
	ft_memset(renderer->map, 0, sizeof(t_map));
	ft_memset(renderer->camera, 0, sizeof(t_camera));
	renderer->need_redraw = 1;
	if (init_renderer(renderer) == EXIT_FAILURE
		|| init_map(renderer, filename) == EXIT_FAILURE
		|| init_camera(renderer) == EXIT_FAILURE
		|| setup_event_hooks(renderer) == EXIT_FAILURE)
	{
		log_error("Error: Failed to initialize one or more renderer elements");
		cleanup(renderer);
		return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}

int	draw_window(t_renderer *renderer)
{
	if (renderer->need_redraw)
	{
		memset(renderer->image->pixels, 0,
			renderer->image->width * renderer->image->height * 4);
		render_map(renderer);
		mlx_image_to_window(renderer->mlx, renderer->image, 0, 0);
		renderer->need_redraw = false;
	}
	return (EXIT_SUCCESS);
}
