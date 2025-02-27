/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_mov.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okhourss <okhourss@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/25 17:06:30 by okhourss          #+#    #+#             */
/*   Updated: 2025/02/27 20:49:23 by okhourss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void print_moves(char *str, int count)
{
	ft_putstr(str);
	ft_putnbr(count);
	ft_putstr("\n");
}

static int is_valid_move(t_game *game, t_position new_pos)
{
	if (new_pos.row < 0 || new_pos.row >= game->map->rows || new_pos.col < 0 || new_pos.col >= game->map->cols)
		return (0);
	if (game->map->grid[new_pos.row][new_pos.col] == '1')
		return (0);
	if (game->map->grid[new_pos.row][new_pos.col] == 'E' && game->map->coin != game->collected_coins)
		return (0);
	return (1);
}

static void handle_player_move(t_game *game, t_position old_pos,
							   t_position new_pos)
{
	if (game->map->grid[new_pos.row][new_pos.col] == 'C')
	{
		game->collected_coins++;
		if (game->map->coin == game->collected_coins)
			mlx_put_image_to_window(game->mlx, game->win, game->open_door,
									game->map->door_col * 64, game->map->door_row * 64);
	}
	if (game->map->grid[new_pos.row][new_pos.col] == 'E' && game->map->coin == game->collected_coins)
	{
		ft_putstr("You won!\n");
		close_game(game, EXIT_SUCCESS);
	}
	mlx_put_image_to_window(game->mlx, game->win, game->grass, old_pos.col * 64,
							old_pos.row * 64);
	mlx_put_image_to_window(game->mlx, game->win, game->player, new_pos.col * 64, new_pos.row * 64);
	game->map->grid[new_pos.row][new_pos.col] = 'P';
	game->map->grid[old_pos.row][old_pos.col] = '0';
	game->moves_count++;
	print_moves("movements count: ", game->moves_count);
}

void move_player(t_game *game, int row_delta, int col_delta)
{
	t_position old_pos;
	t_position new_pos;

	find_player(game->map, &old_pos.row, &old_pos.col);
	new_pos.row = old_pos.row + row_delta;
	new_pos.col = old_pos.col + col_delta;
	if (!is_valid_move(game, new_pos))
		return;
	handle_player_move(game, old_pos, new_pos);
}

int key_hook(int keycode, void *param)
{
	t_game *game;

	game = (t_game *)param;
	if (keycode == 119)
		move_player(game, -1, 0);
	else if (keycode == 115)
		move_player(game, 1, 0);
	else if (keycode == 97)
		move_player(game, 0, -1);
	else if (keycode == 100)
		move_player(game, 0, 1);
	else if (keycode == XK_Escape)
		close_game(game, EXIT_FAILURE);
	return (0);
}
