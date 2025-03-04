/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fvon-der <fvon-der@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/28 15:25:03 by fvon-der          #+#    #+#             */
/*   Updated: 2025/02/26 15:12:00 by fvon-der         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	cleanup(t_renderer *renderer)
{
	if (renderer)
	{
		free_map(renderer->map);
		renderer->map = NULL;
		mlx_terminate(renderer->mlx);
		free(renderer->camera);
		renderer->camera = NULL;
		free(renderer);
		renderer = NULL;
	}
	return (EXIT_SUCCESS);
}
