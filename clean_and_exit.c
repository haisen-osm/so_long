/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean_and_exit.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okhourss <okhourss@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/25 17:03:33 by okhourss          #+#    #+#             */
/*   Updated: 2025/02/25 17:03:33 by okhourss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void exit_error(char *err, t_game *game, char *str, char **arr)
{
	write(2, "Error\n", 6);
	if (err)
		write(2, err, ft_strlen(err));
	if (str)
		free(str);
	if (arr)
		free_2dmap(arr);
	if (game)
		close_game(game, EXIT_FAILURE);
	exit(EXIT_FAILURE);
}

void free_2dmap(char **grid)
{
	int i;

	i = 0;
	while (grid[i])
	{
		free(grid[i]);
		i++;
	}
	free(grid);
}

int close_game(t_game *game, int status)
{
	if (game->player)
		mlx_destroy_image(game->mlx, game->player);
	if (game->diamond)
		mlx_destroy_image(game->mlx, game->diamond);
	if (game->wall)
		mlx_destroy_image(game->mlx, game->wall);
	if (game->grass)
		mlx_destroy_image(game->mlx, game->grass);
	if (game->broke_door)
		mlx_destroy_image(game->mlx, game->broke_door);
	if (game->open_door)
		mlx_destroy_image(game->mlx, game->open_door);
	if (game->win)
		mlx_destroy_window(game->mlx, game->win);
	if (game->mlx)
	{
		mlx_destroy_display(game->mlx);
		free(game->mlx);
	}
	if (game->map->grid)
		free_2dmap(game->map->grid);
	exit(status);
	return (0);
}
