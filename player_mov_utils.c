/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_mov_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okhourss <okhourss@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/27 20:49:34 by okhourss          #+#    #+#             */
/*   Updated: 2025/02/27 20:49:34 by okhourss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	find_door(t_map *map)
{
	int	i;
	int	j;

	i = 0;
	while (i < map->rows)
	{
		j = 0;
		while (map->grid[i][j])
		{
			if (map->grid[i][j] == 'E')
			{
				map->door_row = i;
				map->door_col = j;
				return ;
			}
			j++;
		}
		i++;
	}
}
