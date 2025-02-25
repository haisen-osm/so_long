/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initializing.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okhourss <okhourss@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/25 16:44:37 by okhourss          #+#    #+#             */
/*   Updated: 2025/02/25 17:27:30 by okhourss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void initialize_map(t_map *map)
{
	map->rows = 0;
	map->is_valid = 1;
	map->player = 0;
	map->coin = 0;
	map->exitDoor = 0;
	map->extra_char = 0;
	find_door(map);
}

void xpm_to_image(void *img, void *mlx, char *path)
{
	int x;
	int y;

	x = 64;
	y = 64;
	img = mlx_xpm_file_to_image(mlx, path, &x, &y);
	if (!img)
		exit_error(ERR_MLX_FAILED, 0);
}

void game_init(t_map *map, t_game *game)
{
	game->mlx = mlx_init();
	if (!game->mlx)
		exit_error(ERR_MLX_FAILED, 0);
	game->map = map;
	game->win = mlx_new_window(game->mlx, game->map->cols * 64, game->map->rows * 64, GAME_TITLE);
	if (!game->win)
		exit_error(ERR_MLX_FAILED, 0);
	xpm_to_image(game->player, game->mlx, "textures/player.xpm");
	xpm_to_image(game->diamond, game->mlx, "textures/diamond.xpm");
	xpm_to_image(game->wall, game->mlx, "textures/wall.xpm");
	xpm_to_image(game->grass, game->mlx, "textures/stone.xpm");
	xpm_to_image(game->broke_door, game->mlx, "textures/closed_exit.xpm");
	xpm_to_image(game->open_door, game->mlx, "textures/open_exit.xpm");
	game->collected_coins = 0;
	game->moves_count = 0;
}
