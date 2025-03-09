/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fvon-de <fvon-der@student.42heilbronn.d    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/04 11:18:43 by fvon-de           #+#    #+#             */
/*   Updated: 2025/03/09 07:16:12 by fvon-de          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	init_map(t_map *map)
{
	ft_printf("DEGUB : [init map]\n");
	map->beta = 0.464;
	map->alpha = map->beta / 2;
	map->xrotate = 0;
	map->yrotate = 0;
	map->zrotate = 0;
	map->x_offset = WIDTH / 2;
	map->y_offset = HEIGHT / 2;
	map->zoom = 1;
	map->zscale = 1;
	map->use_zcolor = false;
	map->high = INT_MIN;
	map->low = INT_MAX;
	map->rows = 0;
	map->cols = 0;
	map->grid = NULL;
	map->grid_virt = NULL;
}


static void	malloc_grid(t_map *map)
{
	int	i;

	map->grid_virt = malloc(sizeof(t_point_virt *) * map->rows);
	map->grid = malloc(sizeof(t_point *) * map->rows);
	if (!(map->grid) || !(map->grid_virt))
	{
		free_map(map);
		log_error("[malloc_grid] Allocatione Error");
	}
	i = -1;
	while (++i < map->rows)
	{
		map->grid_virt[i] = malloc(sizeof(t_point_virt) * map->cols);
		map->grid[i] = malloc(sizeof(t_point) * map->cols);
		if (!(map->grid[i]) || !(map->grid_virt[i]))
		{
			if (i + 1 < map->rows)
			{
				map->grid_virt[i + 1] = NULL;
				map->grid[i + 1] = NULL;
			}
			free_map(map);
			log_error("[malloc_grid] Allocatione Error");
		}
	}
}

t_map	*get_map(t_map *map, char *filename)
{
	int		fd;

	init_map(map);
	fd = open(filename, O_RDONLY);
	if (fd == -1)
	{
		log_error("Error: [get_map] Cant open file");
		free(map);
		return (NULL);
	}
	get_dimensions(fd, map);
	ft_printf("DEBUG: [get_map] Dimensions: Rows=%d, Cols=%d\n", map->rows, map->cols);
	close(fd);
	fd = open(filename, O_RDONLY);
	if (fd == -1)
	{
		log_error("Error: [get_map] Cannot reopen file");
		free(map);
		return (NULL);
	}
	malloc_grid(map);
	parse_map(fd, map);
	close(fd);
	set_zcolor(map);
	return (map);
}
