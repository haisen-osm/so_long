/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_rendring.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okhourss <okhourss@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/25 16:48:58 by okhourss          #+#    #+#             */
/*   Updated: 2025/02/25 17:20:43 by okhourss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void my_mlx_img(t_game *game, void *img, int x, int y)
{
	int mlx_img;

	mlx_img = mlx_put_image_to_window(game->mlx, game->win, img, x, y);
	if (!mlx_img)
		exit_error("Mlx image failed\n", game, NULL, NULL);
}

void map_rendering(t_game *game)
{
	int(i), (j), (yy), (xx);
	i = 0;
	yy = 0;
	while (i < game->map->rows)
	{
		j = 0;
		xx = 0;
		while (j < game->map->cols)
		{
			if (game->map->grid[i][j] == '1')
				my_mlx_img(game, game->wall, xx, yy);
			else if (game->map->grid[i][j] == '0')
				my_mlx_img(game, game->grass, xx, yy);
			else if (game->map->grid[i][j] == 'P')
				my_mlx_img(game, game->player, xx, yy);
			else if (game->map->grid[i][j] == 'C')
				my_mlx_img(game, game->diamond, xx, yy);
			else if (game->map->grid[i][j] == 'E')
				my_mlx_img(game, game->broke_door, xx, yy);
			xx += 64;
			j++;
		}
		yy += 64;
		i++;
	}
}
