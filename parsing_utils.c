/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okhourss <okhourss@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/25 16:47:24 by okhourss          #+#    #+#             */
/*   Updated: 2025/02/25 17:15:08 by okhourss         ###   ########.fr       */
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

void flood_fill(t_map *map, int row, int col, char **map_copy,
				int *exit_found, int *coin_found)
{
	if (row < 0 || col < 0 || row >= map->rows || col >= map->cols)
		return;
	if (map_copy[row][col] == '1' || map_copy[row][col] == 'V')
		return;
	if (map_copy[row][col] == 'C')
		(*coin_found)++;
	if (map_copy[row][col] == 'E')
		(*exit_found) = 1;
	map_copy[row][col] = 'V';
	flood_fill(map, row + 1, col, map_copy, exit_found, coin_found);
	flood_fill(map, row - 1, col, map_copy, exit_found, coin_found);
	flood_fill(map, row, col + 1, map_copy, exit_found, coin_found);
	flood_fill(map, row, col - 1, map_copy, exit_found, coin_found);
}
