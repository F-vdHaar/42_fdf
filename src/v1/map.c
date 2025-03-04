/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fvon-der <fvon-der@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/28 15:54:35 by fvon-der          #+#    #+#             */
/*   Updated: 2025/02/27 08:04:23 by fvon-der         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static t_list	*read_file(const char *filename, int *line_count);
static int		fill_map(t_map *map, t_list *lines);
static int		parse_grid_and_color(t_map *map, char *num_str, int i, int j);

int	init_map(t_renderer *renderer, const char *filename)
{
	t_map	*map;

	map = renderer->map;
	if (!map)
	{
		log_error("Failed to allocate memory for map");
		exit(EXIT_FAILURE);
	}
	(map)->file_content = read_file(filename, &(map)->height);
	if (!(map)->file_content)
	{
		cleanup(renderer);
		exit(EXIT_FAILURE);
	}
	(map)->width = count_words(((char *)(map)->file_content->content), ' ');
	(map)->grid = allocate_map((map)->height, (map)->width);
	(map)->color = allocate_map(map->height, map->width);
	if (!(map)->grid || (fill_map(map, (map)->file_content) == EXIT_FAILURE))
	{
		free_map(map);
		exit(EXIT_FAILURE);
	}
	find_z_bounds(map);
	renderer->map = map;
	return (EXIT_SUCCESS);
}

static t_list	*read_file(const char *filename, int *line_count)
{
	int		fd;
	char	*line;
	char	*trimmed_line;
	t_list	*lines;

	lines = NULL;
	*line_count = 0;
	fd = open(filename, O_RDONLY);
	if (fd < 0)
		return (NULL);
	line = get_next_line(fd);
	while (line != NULL)
	{
		trimmed_line = ft_trim(line, "\n");
		free(line);
		ft_lstadd_back(&lines, ft_lstnew(trimmed_line));
		(*line_count)++;
		line = get_next_line(fd);
	}
	close(fd);
	return (lines);
}

static int	parse_grid_and_color(t_map *map, char *num_str, int i, int j)
{
	char	*comma;

	comma = ft_strchr(num_str, ',');
	map->grid[i][j] = ft_atoi(num_str);
	if (comma && comma + 3)
		map->color[i][j] = ft_atoi_base(comma + 3, "0123456789ABCDEF");
	else
		map->color[i][j] = 0xFFFFFF;
	return (EXIT_SUCCESS);
}

static int	fill_map(t_map *map, t_list *lines)
{
	char	**nums;
	int		i;
	int		j;

	i = 0;
	while (i < map->height)
	{
		nums = ft_split(lines->content, ' ');
		if (!nums)
			return (EXIT_FAILURE);
		j = 0;
		while (j < map->width)
		{
			if (parse_grid_and_color(map, nums[j], i, j) == EXIT_FAILURE)
			{
				return (free(nums), EXIT_FAILURE);
			}
			free(nums[j]);
			j++;
		}
		free(nums);
		i++;
		lines = lines->next;
	}
	return (EXIT_SUCCESS);
}
