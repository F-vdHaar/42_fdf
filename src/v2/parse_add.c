/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_add.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fvon-de <fvon-der@student.42heilbronn.d    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/12 17:56:09 by fvon-de           #+#    #+#             */
/*   Updated: 2025/03/12 17:56:52 by fvon-de          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static int	get_cols(char *line);

int	parse_color(int fd, t_map *map, char *tabj)
{
	char	*color_str;
	int		color;

	color_str = tabj;
	while (*color_str == '-')
		color_str++;
	while (ft_isdigit(*color_str))
		color_str++;
	if (*color_str != ',' || (ft_strncmp(color_str + 1, "0X", 2)
			&& ft_strncmp(color_str + 1, "0x", 2)))
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

void	free_and_close(int fd, t_map *map, char **tab, char *line)
{
	if (tab)
		ft_free_tab((void **)tab, map->cols);
	if (line)
		free(line);
	close(fd);
	free_map(map);
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
