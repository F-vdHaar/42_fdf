/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fvon-de <fvon-der@student.42heilbronn.d    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/28 15:21:33 by fvon-der          #+#    #+#             */
/*   Updated: 2025/02/23 14:42:58 by fvon-de          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"


int main(int argc, char **argv)
{
	t_renderer	*renderer = NULL;

	if (argc != 2)
	{
		ft_printf("Usage: %s <map_file>\n", argv[0]);
		return EXIT_FAILURE;
	}
	if (!(renderer = malloc(sizeof(t_renderer)))) {
		log_error("Error: Failed to allocate memory for renderer");
		return EXIT_FAILURE;
	}
	ft_memset(renderer, 0, sizeof(t_renderer));
	if (initialize(renderer, argv[1]) == EXIT_FAILURE)
	{ 
		free(renderer); // Free if init fails
		return EXIT_FAILURE;
	}
	draw_window(renderer);
	mlx_loop_hook(renderer->mlx.mlx_ptr, process_events_wrapper, renderer);
	mlx_loop(renderer->mlx.mlx_ptr);
	cleanup(renderer);
	renderer = NULL;
	return (EXIT_SUCCESS);
}

int initialize(t_renderer *renderer, char *filename)
{
	renderer->map = malloc(sizeof(t_map));
	renderer->camera = malloc(sizeof(t_camera));
	renderer->mouse = malloc(sizeof(t_mouse));
	renderer->event_queue = malloc(sizeof(t_event_queue));
	if (!renderer->map || !renderer->camera || !renderer->mouse || !renderer->event_queue ) {
		log_error("Error: Failed to allocate memory for one or more renderer elements");
		cleanup(renderer);
		renderer = NULL;
		return (EXIT_FAILURE);
	}
	ft_memset(renderer->map, 0, sizeof(t_map));
	ft_memset(renderer->camera, 0, sizeof(t_camera));
	ft_memset(renderer->mouse, 0, sizeof(t_mouse));
	ft_memset(renderer->event_queue, 0, sizeof(t_event_queue));
	if (init_renderer(renderer) == EXIT_FAILURE || 
	init_map(renderer, filename) == EXIT_FAILURE ||
	init_camera(renderer) == EXIT_FAILURE ||
	init_mouse(renderer) == EXIT_FAILURE ||
	setup_event_hooks(renderer) == EXIT_FAILURE)
	{
		log_error("Error: Failed to initialize one or more renderer elements");
		cleanup(renderer);
		return EXIT_FAILURE;
	}
	return EXIT_SUCCESS;
}


int	draw_window(t_renderer *renderer)
{
	
    mlx_clear_window(renderer->mlx.mlx_ptr, renderer->mlx.win_ptr);
    renderer->mlx.img_ptr = mlx_new_image(renderer->mlx.mlx_ptr, renderer->win_width, renderer->win_height);
    renderer->mlx.img_data = mlx_get_data_addr(renderer->mlx.img_ptr, &renderer->mlx.bits_per_pixel, &renderer->mlx.line_length, &renderer->mlx.endian);

	//debug_render_grid(renderer); 
	render_map(renderer);
	//draw_pixel(renderer, 200, 200, 0xFF0000);
	mlx_put_image_to_window(renderer->mlx.mlx_ptr, renderer->mlx.win_ptr,
		renderer->mlx.img_ptr, 0, 0);
	return (EXIT_SUCCESS);
}
