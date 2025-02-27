/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_mov.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okhourss <okhourss@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/25 17:06:30 by okhourss          #+#    #+#             */
/*   Updated: 2025/02/25 21:40:06 by okhourss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void find_door(t_map *map)
{
	int i;
	int j;

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
				return;
			}
			j++;
		}
		i++;
	}
}

void print_moves(char *str, int count)
{
	ft_putstr(str);
	ft_putnbr(count);
	ft_putstr("\n");
}
static int is_valid_move(t_game *game, int new_row, int new_col)
{
	if (new_row < 0 || new_row >= game->map->rows || new_col < 0 || new_col >= game->map->cols)
		return (0);
	if (game->map->grid[new_row][new_col] == '1')
		return (0);
	if (game->map->grid[new_row][new_col] == 'E' && game->map->coin != game->collected_coins)
		return (0);
	return (1);
}

static void handle_player_move(t_game *game, int row, int col, int new_row,
							   int new_col)
{
	if (game->map->grid[new_row][new_col] == 'C')
	{
		game->collected_coins++;
		if (game->map->coin == game->collected_coins)
			mlx_put_image_to_window(game->mlx, game->win, game->open_door,
									game->map->door_col * 64, game->map->door_row * 64);
	}
	if (game->map->grid[new_row][new_col] == 'E' && game->map->coin == game->collected_coins)
	{
		ft_putstr("You won!\n");
		close_game(game, EXIT_SUCCESS);
	}
	mlx_put_image_to_window(game->mlx, game->win, game->grass, col * 64, row * 64);
	mlx_put_image_to_window(game->mlx, game->win, game->player, new_col * 64,
							new_row * 64);
	game->map->grid[new_row][new_col] = 'P';
	game->map->grid[row][col] = '0';
	game->moves_count++;
	print_moves("movements count: ", game->moves_count);
}

void move_player(t_game *game, int row_delta, int col_delta)
{
	int row;
	int col;
	int new_row;
	int new_col;

	find_player(game->map, &row, &col);
	new_row = row + row_delta;
	new_col = col + col_delta;
	if (!is_valid_move(game, new_row, new_col))
		return;
	handle_player_move(game, row, col, new_row, new_col);
}

int key_hook(int keycode, void *param)
{
	t_game *game = (t_game *)param;

	if (keycode == 119)
		move_player(game, -1, 0);
	else if (keycode == 115)
		move_player(game, 1, 0);
	else if (keycode == 97)
		move_player(game, 0, -1);
	else if (keycode == 100)
		move_player(game, 0, 1);
	// else if (keycode == XK_Escape)
	// 	close_game(game);
	return (0);
}