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

void	find_player(t_map *map, int *row, int *col)
{
	int	i;
	int	j;

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
				return ;
			}
			j++;
		}
		i++;
	}
}

void	flood_fill(t_map *map, t_flood *flood, int col, int row)
{
	if (row < 0 || col < 0 || row >= map->rows || col >= map->cols)
		return ;
	if (map->grid_copy[row][col] == '1' || map->grid_copy[row][col] == 'V')
		return ;
	if (map->grid_copy[row][col] == 'C')
		flood->coin_found++;
	if (map->grid_copy[row][col] == 'E')
	{
		flood->exit_found = 1;
		map->grid_copy[row][col] = 'V';
		return ;
	}
	map->grid_copy[row][col] = 'V';
	flood_fill(map, flood, col + 1, row);
	flood_fill(map, flood, col - 1, row);
	flood_fill(map, flood, col, row + 1);
	flood_fill(map, flood, col, row - 1);
}
