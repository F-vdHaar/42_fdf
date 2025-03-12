/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fvon-de <fvon-der@student.42heilbronn.d    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/09 07:19:36 by fvon-de           #+#    #+#             */
/*   Updated: 2025/03/12 17:38:55 by fvon-de          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static int	parse_column(int fd, t_map *map, char **tab, int i);
static int	process_line(int fd, t_map *map, int i);
static void	process_z_value(t_map *map, t_point_virt *virt_point, int z_value);
static void	calculate_offsets(t_map *map, int *x_offset, int *y_offset);
static int	get_cols(char *line);

static void	process_z_value(t_map *map, t_point_virt *virt_point, int z_value)
{
	virt_point->z = (double)z_value * map->interval;
	map->high = ft_max(map->high, virt_point->z);
	map->low = ft_min(map->low, virt_point->z);
}

static void	calculate_offsets(t_map *map, int *x_offset, int *y_offset)
{
	*x_offset = (map->cols - 1) * map->interval / 2;
	*y_offset = (map->rows - 1) * map->interval / 2;
}

static int	parse_column(int fd, t_map *map, char **tab, int i)
{
	int				x_offset;
	int				y_offset;
	int				j;
	int				z_value;
	t_point_virt	*virt_point;

	calculate_offsets(map, &x_offset, &y_offset);
	j = 0;
	while (tab[j] && j < map->cols)
	{
		z_value = ft_atoi(tab[j]);
		virt_point = &(map->grid_virt[i][j]);
		virt_point->x = (double)j * map->interval - x_offset;
		virt_point->y = (double)i * map->interval - y_offset;
		process_z_value(map, virt_point, z_value);
		virt_point->col = parse_color(fd, map, tab[j]);
		j++;
	}
	return (0);
}

static int	process_line(int fd, t_map *map, int i)
{
	char	*line;
	char	*temp;
	char	**tab;

	temp = get_next_line(fd);
	if (!temp)
	{
		free_and_close(fd, map, NULL, NULL);
		return (1);
	}
	line = ft_strtrim(temp, "\n");
	free(temp);
	if (!line)
	{
		free_and_close(fd, map, NULL, NULL);
		return (1);
	}
	tab = ft_split(line, ' ');
	free(line);
	if (!tab)
		return (free_and_close(fd, map, NULL, NULL), 1);
	if (parse_column(fd, map, tab, i))
		return (ft_free_tab((void **)tab, map->cols), 1);
	ft_free_tab((void **)tab, map->cols);
	return (0);
}

void	parse_map(int fd, t_map *map)
{
	int	i;

	if (fd < 0)
		return ;
	i = 0;
	while (i < map->rows)
	{
		if (process_line(fd, map, i))
		{
			close(fd);
			return ;
		}
		i++;
	}
	close(fd);
}

void	free_and_close(int fd, t_map *map, char **tab, char *line)
{
	if (tab)
		ft_free_tab((void **)tab, map->cols);
	if (line)
		free(line);
	close(fd);
	free_map(map);
}

int	parse_color(int fd, t_map *map, char *tabj)
{
	char	*color_str;
	int		color;

	color_str = tabj;
	while (*color_str == '-')
		color_str++;
	while (ft_isdigit(*color_str))
		color_str++;
	if (*color_str != ',' || (ft_strncmp(color_str + 1, "0X", 2) &&
		ft_strncmp(color_str + 1, "0x", 2)))
	{
		return (0xFFFFFFFF);
	}
	color_str += 2;
	ft_striteri(color_str, &make_upper);
	color = ft_atoi_base(color_str, "0123456789ABCDEF");
	if (color == -1)
		return (0xFFFFFFFF);
	return ((color << 8) | 0xFF);
}

int	get_dimensions(int fd, t_map *map)
{
	char	*line;

	line = get_next_line(fd);
	if (!line)
	{
		close(fd);
		return (free_map(map), EXIT_FAILURE);
	}
	map->cols = get_cols(line);
	free(line);
	if (!map->cols)
	{
		close(fd);
		return (free_map(map), EXIT_FAILURE);
	}
	map->rows = 1;
	line = get_next_line(fd);
	while (line)
	{
		free(line);
		line = get_next_line(fd);
		map->rows++;
	}
	close(fd);
	return (EXIT_SUCCESS);
}

static int	get_cols(char *line)
{
	char	*trimmed_line;
	char	**tab;
	int		i;

	trimmed_line = ft_strtrim(line, "\n");
	tab = ft_split(trimmed_line, ' ');
	free(trimmed_line);
	if (!tab)
		return (0);
	i = 0;
	while (tab[i])
		i++;
	ft_free_tab((void **)tab, i);
	return (i);
}