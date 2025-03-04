/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fvon-der <fvon-der@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/04 13:55:06 by fvon-der          #+#    #+#             */
/*   Updated: 2025/02/27 07:42:55 by fvon-der         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fdf.h>

static	void	del_content(void *content);

static void	del_content(void *content)
{
	free(content);
}

int	count_words(const char *str, char delimiter)
{
	int	count;
	int	i;

	count = 0;
	i = 0;
	while (str[i])
	{
		while (str[i] && str[i] == delimiter)
			i++;
		if (str[i] && str[i] != delimiter)
		{
			count++;
			while (str[i] && str[i] != delimiter)
				i++;
		}
	}
	return (count);
}

int	**allocate_map(int height, int width)
{
	int	**map;
	int	i;

	map = (int **)malloc(sizeof(int *) * height);
	if (!map)
		return (NULL);
	i = 0;
	while (i < height)
	{
		map[i] = (int *)malloc(sizeof(int) * width);
		if (!map[i])
		{
			while (--i >= 0)
				free(map[i]);
			free(map);
			return (NULL);
		}
		i++;
	}
	return (map);
}

int	free_map(t_map *map)
{
	int	i;

	if (!map)
		return (EXIT_SUCCESS);
	if (map->grid || map->color)
	{
		i = 0;
		while (i < map->height)
		{
			if (map->grid)
				free(map->grid[i]);
			if (map->color)
				free(map->color[i]);
			i++;
		}
		free(map->grid);
		free(map->color);
	}
	if (map->file_content)
		ft_lstclear(&map->file_content, del_content);
	free(map);
	return (EXIT_SUCCESS);
}

int	find_z_bounds(t_map *map)
{
	int	i;
	int	j;

	map->z_min = INT_MAX;
	map->z_max = INT_MIN;
	i = 0;
	while (i < map->height)
	{
		j = 0;
		while (j < map->width)
		{
			if (map->grid[i][j] < map->z_min)
				map->z_min = map->grid[i][j];
			if (map->grid[i][j] > map->z_max)
				map->z_max = map->grid[i][j];
			j++;
		}
		i++;
	}
	return (EXIT_SUCCESS);
}
