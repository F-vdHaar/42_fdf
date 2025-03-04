/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   projection.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fvon-der <fvon-der@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/24 17:42:27 by fvon-de           #+#    #+#             */
/*   Updated: 2025/02/27 08:05:54 by fvon-der         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static void		center_map(t_renderer *renderer, t_point *projected);
static t_point	apply_projection(t_renderer *renderer, t_point point,
					float scale);

t_point	project_point(t_renderer *renderer, int x, int y, int z)
{
	t_point	point;
	t_point	projected;
	float	scale;

	point.x = x;
	point.y = y;
	point.z = z;
	point = rotate_point(renderer, point);
	if (renderer->camera->z_height == 0)
		scale = 0;
	else
		scale = renderer->camera->zoom / renderer->camera->z_height;
	projected = apply_projection(renderer, point, scale);
	center_map(renderer, &projected);
	return (projected);
}

static void	center_map(t_renderer *renderer, t_point *projected)
{
	projected->x += renderer->camera->x_offset;
	projected->y += renderer->camera->y_offset;
}

static t_point	apply_projection(t_renderer *renderer,
		t_point point, float scale)
{
	t_point	projected;
	float	temp_x;
	float	temp_y;

	if (renderer->camera->iso == 1)
	{
		temp_x = point.x * scale * renderer->camera->x_scale * 0.7071f;
		temp_y = point.y * scale * renderer->camera->y_scale * 0.7071f;
		projected.x = temp_x - temp_y;
		projected.y = ((point.x + point.y) * scale * 0.7071f)
			- (point.z * scale * renderer->camera->z_scale);
	}
	else if (renderer->camera->iso == -1)
	{
		projected.x = point.x * scale * renderer->camera->x_scale;
		projected.y = point.y * scale * renderer->camera->y_scale;
	}
	projected.z = point.z;
	return (projected);
}
