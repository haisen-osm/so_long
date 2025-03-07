/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initializing.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okhourss <okhourss@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/25 16:44:37 by okhourss          #+#    #+#             */
/*   Updated: 2025/03/07 21:46:10 by okhourss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	initialize_map(t_map *map)
{
	map->rows = 0;
	map->is_valid = 1;
	map->player = 0;
	map->coin = 0;
	map->exit_door = 0;
	map->extra_char = 0;
}

void	xpm_to_image(void **img, t_game *game, char *path)
{
	int	x;
	int	y;

	x = 64;
	y = 64;
	*img = mlx_xpm_file_to_image(game->mlx, path, &x, &y);
	if (!(*img))
		exit_error(ERR_MLX_XPM_TO_IMG, game, NULL, NULL);
}

void	ini_game(t_game *game)
{
	game->broke_door = NULL;
	game->collected_coins = 0;
	game->moves_count = 0;
	game->diamond = NULL;
	game->grass = NULL;
	game->map = NULL;
	game->mlx = NULL;
	game->open_door = NULL;
	game->player = NULL;
	game->wall = NULL;
	game->win = NULL;
}

void	game_init(t_map *map, t_game *game)
{
	ini_game(game);
	game->mlx = mlx_init();
	if (!game->mlx)
		exit_error(ERR_MLX_FAILED, NULL, NULL, map->grid);
	game->map = map;
	game->win = mlx_new_window(game->mlx, game->map->cols * 64, game->map->rows
			* 64, GAME_TITLE);
	if (!game->win)
		exit_error(ERR_MLX_FAILED, game, NULL, NULL);
	xpm_to_image(&game->player, game, "textures/player.xpm");
	xpm_to_image(&game->diamond, game, "textures/diamond.xpm");
	xpm_to_image(&game->wall, game, "textures/wall.xpm");
	xpm_to_image(&game->grass, game, "textures/stone.xpm");
	xpm_to_image(&game->broke_door, game, "textures/closed_exit.xpm");
	xpm_to_image(&game->open_door, game, "textures/open_exit.xpm");
}
