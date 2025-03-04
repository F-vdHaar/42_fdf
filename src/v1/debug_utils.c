/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fvon-der <fvon-der@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/14 14:45:39 by fvon-de           #+#    #+#             */
/*   Updated: 2025/02/27 08:40:11 by fvon-der         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

/* static void	draw_square(t_renderer *renderer, int x, int y, int color); */

int	debug_print_nums_char(char **nums)
{
	int	i;

	i = 0;
	if (!nums)
	{
		ft_printf("DEBUG : nums is NULL\n");
		return (EXIT_FAILURE);
	}
	while (nums[i])
	{
		ft_printf("DEBUG : nums[%d]: \"%s\"\n", i, nums[i]);
		i++;
	}
	return (EXIT_SUCCESS);
}

int	debug_print_map(t_renderer *renderer)
{
	int	i;
	int	j;

	i = 0;
	while (i < renderer->map->height)
	{
		j = 0;
		while (j < renderer->map->width)
		{
			ft_printf("%d ", renderer->map->grid[i][j]);
			j++;
		}
		write(1, "\n", sizeof(char));
		i++;
	}
	i = 0;
	while (i < renderer->map->height)
	{
		j = 0;
		while (j < renderer->map->width)
			j++;
		write(1, "\n", sizeof(char));
		i++;
	}
	return (EXIT_SUCCESS);
}

/* static void	draw_square(t_renderer *renderer, int x, int y, int color)
{
	int	square_size;
	int	i;
	int	j;

	square_size = 10;
	i = x;
	while (i < x + square_size)
	{
		j = y;
		while (j < y + square_size)
		{
			if (i < renderer->win_width && j < renderer->win_height)
			{
				put_pixel(renderer, i, j, color);
			}
			j++;
		}
		i++;
	}
} */

/* int	debug_render_grid(t_renderer *renderer)
{
	int		x;
	int		y;

	y = 0;
	while (y < renderer->map->height)
	{
		x = 0;
		while (x < renderer->map->width)
		{
			draw_square(renderer, x * 20, y * 20,
				get_grid_color(renderer->map->grid[y][x]));
			x++;
		}
		y++;
	}
	return (EXIT_SUCCESS);
} */
