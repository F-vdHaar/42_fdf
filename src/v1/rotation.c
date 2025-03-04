/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rotation.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fvon-der <fvon-der@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/24 17:37:02 by fvon-de           #+#    #+#             */
/*   Updated: 2025/02/27 07:31:52 by fvon-der         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static void	create_rotation_matrices(t_renderer *renderer,
				float rot_x[3][3], float rot_y[3][3], float rot_z[3][3]);
static void	set_matrix(float m[3][3], float a, float b, char axis);
static void	init_identity_matrix(float m[3][3]);

t_point	rotate_point(t_renderer *renderer, t_point point)
{
	float	rx[3][3];
	float	ry[3][3];
	float	rz[3][3];
	t_point	rotated;

	create_rotation_matrices(renderer, rx, ry, rz);
	rotated.x = point.x * rz[0][0] + point.y * rz[0][1] + point.z * rz[0][2];
	rotated.y = point.x * rz[1][0] + point.y * rz[1][1] + point.z * rz[1][2];
	rotated.z = point.x * rz[2][0] + point.y * rz[2][1] + point.z * rz[2][2];
	point = rotated;
	rotated.x = point.x * ry[0][0] + point.y * ry[0][1] + point.z * ry[0][2];
	rotated.y = point.x * ry[1][0] + point.y * ry[1][1] + point.z * ry[1][2];
	rotated.z = point.x * ry[2][0] + point.y * ry[2][1] + point.z * ry[2][2];
	point = rotated;
	rotated.x = point.x * rx[0][0] + point.y * rx[0][1] + point.z * rx[0][2];
	rotated.y = point.x * rx[1][0] + point.y * rx[1][1] + point.z * rx[1][2];
	rotated.z = point.x * rx[2][0] + point.y * rx[2][1] + point.z * rx[2][2];
	return (rotated);
}

static void	init_identity_matrix(float m[3][3])
{
	int	i;
	int	j;

	i = -1;
	while (++i < 3)
	{
		j = -1;
		while (++j < 3)
			m[i][j] = (i == j);
	}
}

static void	set_matrix(float m[3][3], float a, float b, char axis)
{
	init_identity_matrix(m);
	if (axis == 'x')
	{
		m[1][1] = a;
		m[1][2] = -b;
		m[2][1] = b;
		m[2][2] = a;
	}
	else if (axis == 'y')
	{
		m[0][0] = a;
		m[0][2] = b;
		m[2][0] = -b;
		m[2][2] = a;
	}
	else if (axis == 'z')
	{
		m[0][0] = a;
		m[0][1] = -b;
		m[1][0] = b;
		m[1][1] = a;
	}
}

static void	create_rotation_matrices(t_renderer *renderer,
		float rot_x[3][3], float rot_y[3][3], float rot_z[3][3])
{
	float	c;
	float	s;

	c = cos(renderer->camera->x_angle);
	s = sin(renderer->camera->x_angle);
	set_matrix(rot_x, c, s, 'x');
	c = cos(renderer->camera->y_angle);
	s = sin(renderer->camera->y_angle);
	set_matrix(rot_y, c, s, 'y');
	c = cos(renderer->camera->z_angle);
	s = sin(renderer->camera->z_angle);
	set_matrix(rot_z, c, s, 'z');
}
