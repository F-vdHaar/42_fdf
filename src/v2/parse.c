/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fvon-de <fvon-der@student.42heilbronn.d    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/09 07:19:36 by fvon-de           #+#    #+#             */
/*   Updated: 2025/03/09 08:00:17 by fvon-de          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static int parse_color(int fd, t_map *map, char *tabj) {
    int color;
    char *color_str;

    color_str = tabj;
    while (*color_str == '-')
        color_str++;
    while (ft_isdigit(*color_str))
        color_str++;
    if (*color_str == ',')
        color_str++;
    else
        return (0xFFFFFFFF);
    if ((ft_strncmp(color_str, "0X", 2) && ft_strncmp(color_str, "0x", 2))) {
        log_error("[parse_color] Invalid color format");
        close(fd);
        free_map(map);
        return (0xFFFFFFFF);
    }
    color_str += 2;
    ft_striteri(color_str, &make_upper);
    color = ft_atoi_base(color_str, "0123456789ABCDEF");
    if (color == -1) {
        log_error("[parse_color] Invalid color value");
        close(fd);
        free_map(map);
        return (0xFFFFFFFF);
    }
    return ((color << 8) | 0xFF);
}

static void parse_column(int fd, t_map *map, char **tab, int i) {
    t_point_virt *virt_point;
    int x_offset;
    int y_offset;
    int j;
    int z_value;

    j = -1;
    while (++j < map->cols) {
        if (!ft_isdigit(*tab[j]) && *tab[j] != '-') {
            log_error("[parse_column] Invalid character in map data");
            close(fd);
            free_map(map);
            return;
        }

        z_value = ft_atoi(tab[j]);

        virt_point = &(map->grid_virt[i][j]);
        x_offset = (map->cols - 1) * map->interval / 2;
        y_offset = (map->rows - 1) * map->interval / 2;
        virt_point->x = (double)j * (map->interval) - x_offset;
        virt_point->y = (double)i * (map->interval) - y_offset;
        virt_point->z = (double)z_value * (map->interval);
        map->high = ft_max(map->high, virt_point->z);
        map->low = ft_min(map->low, virt_point->z);
        virt_point->mapcolor = parse_color(fd, map, tab[j]);
    }
}

void parse_map(int fd, t_map *map)
{
    char *line;
    char *temp;
    char **tab;
    int i;

    i = -1;
	ft_printf("DEBUG [parse_map] FD %i, Rows: %d, Cols: %d\n", fd, map->rows, map->cols);
	if (fd < 0) 
	{
        log_error("[parse_map] Invalid file descriptor");
        return;
    }
    while (++i < map->rows) {
        temp = get_next_line(fd);
        if (!temp) {
            log_error("[parse_map] get_next_line failed");
            close(fd);
            free_map(map);
            return;
        }
        line = ft_strtrim(temp, "\n");
        free(temp);
        if (!line) {
            log_error("[parse_map] ft_strtrim failed");
            close(fd);
            free_map(map);
            return;
        }
        tab = ft_split(line, ' ');
        free(line);
        if (!tab) {
            log_error("[parse_map] ft_split failed");
            close(fd);
            free_map(map);
            return;
        }
        parse_column(fd, map, tab, i);
        ft_free_tab((void **)tab, map->cols);
    }
}


static int get_cols(int fd, t_map *map, char *line) {
    char **tab;
    char *temp;
    int i;
    int first_value_set = 0;

    temp = ft_strtrim(line, "\n");
    free(line);
    if (!temp)
        log_error("[get_cols] ft_strtrim failed");
    tab = ft_split(temp, ' ');
    free(temp);
    if (!tab)
    log_error("[get_cols] ft_split failed");
    i = 0;
    while (tab[i]) {
        int current_value = ft_atoi(tab[i]);
        if (!first_value_set) {
            map->high = current_value;
            map->low = current_value;
            first_value_set = 1;
        } else {
            map->high = ft_max(map->high, current_value);
            map->low = ft_min(map->low, current_value);
        }
        i++;
    }
    ft_free_tab((void **)tab, i);
    return (i);
}

void	get_dimensions(int fd, t_map *map)
{
	char	*line;

	line = get_next_line(fd);
	if (!line)
    {
        close(fd);
        free_map(map);
        log_error("[get_dimension] gnl failed");
    }
	map->cols = get_cols(fd, map, line);
	if (map->cols == 0)
    {
        close(fd);
        free_map(map);
        log_error("[get_dimension] get_cols failed");
    }
	map->rows = 1;
	while (1)
	{
		line = get_next_line(fd);
		if (!line)
			break ;
		map->rows++;
		if (map->cols != get_cols(fd, map, line))
        {
            close(fd);
            free_map(map);
            log_error("[get_dimension] get_cols failed");
        }
		
	}
}
