/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okhourss <okhourss@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/25 16:47:24 by okhourss          #+#    #+#             */
/*   Updated: 2025/02/27 21:07:04 by okhourss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void find_player(t_map *map, int *row, int *col)
{
	int i;
	int j;

	i = 0;
	while (i < map->rows)
	{
		j = 0;
		while (map->grid[i][j])
		{
			if (map->grid[i][j] == 'P')
			{
				*row = i;
				*col = j;
				return;
			}
			j++;
		}
		i++;
	}
}

static void recursive_flood_fill(t_flood *data, int row, int col)
{
	if (row < 0 || col < 0 || row >= data->map->rows || col >= data->map->cols)
		return;
	if (data->map_copy[row][col] == '1' || data->map_copy[row][col] == 'V')
		return;
	if (data->map_copy[row][col] == 'C')
		(*data->coin_found)++;
	if (data->map_copy[row][col] == 'E')
		(*data->exit_found) = 1;
	data->map_copy[row][col] = 'V';
	recursive_flood_fill(data, row + 1, col);
	recursive_flood_fill(data, row - 1, col);
	recursive_flood_fill(data, row, col + 1);
	recursive_flood_fill(data, row, col - 1);
}

void flood_fill(t_map *map, int row, int col, char **map_copy,
				int *exit_found, int *coin_found)
{
	t_flood data;

	data.map = map;
	data.map_copy = map_copy;
	data.row = row;
	data.col = col;
	data.exit_found = exit_found;
	data.coin_found = coin_found;
	recursive_flood_fill(&data, row, col);
}
