/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fvon-der <fvon-der@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/21 15:25:23 by fvon-de           #+#    #+#             */
/*   Updated: 2025/02/25 22:43:50 by fvon-der         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	handle_mlx_close(void *param)
{
	t_renderer	*renderer;

	renderer = (t_renderer *)param;
	if (!renderer)
	{
		return (EXIT_FAILURE);
	}
	cleanup(renderer);
	exit(EXIT_SUCCESS);
	return (EXIT_SUCCESS);
}

int	handle_mlx_resize(int32_t width, int32_t height, void *param)
{
	t_renderer	*renderer;

	renderer = (t_renderer *)param;
	if (!renderer)
	{
		return (EXIT_FAILURE);
	}
	renderer->win_width = width;
	renderer->win_height = height;
	if (renderer->image)
	{
		mlx_resize_image(renderer->image, width, height);
	}
	draw_window(renderer);
	return (EXIT_SUCCESS);
}
