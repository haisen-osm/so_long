/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okhourss <okhourss@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/15 13:09:28 by okhourss          #+#    #+#             */
/*   Updated: 2025/02/19 17:37:21 by okhourss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_LONG_H
#define SO_LONG_H

#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include "minilibx-linux/mlx.h"
#include <X11/keysym.h>
// #include <mlx.h>

typedef struct s_map
{
	size_t rows;
	size_t cols;
	int is_valid;
	int player;
	int coin;
	int exitDoor;
	int extra_char;
	char **grid;
	char **grid_copy;
} t_map;

typedef struct s_game
{
	void *mlx;
	void *win;
	t_map *map;
	int player_x;
	int player_y;
	void *player;
	void *grass;
	void *diamond;
	void *wall;
	void *door;
	int collected_coins;
} t_game;

#define EXTENSTION ".ber"
#define ERR_ARGS "Invalid number of arguments.\n"
#define ERR_EXT "Wrong file extension. Expected '.ber'.\n"
#define ERR_OPEN "Failed to open the file.\n"
#define ERR_EMPTY_LINE "Empty line detected in the map.\n"
#define ERR_INVALID_MAP "Invalid map structure.\n"
#define ERR_NOT_REACHABLE "Not all collectibles are reachable.\n"
#define ERR_MLX_FAILED "Mlx connection failed\n"
#define ERR_WIN_FAIL "Mlx failed creating a window\n"
#define GAME_TITLE "so_long"
#define BUFFER_SIZE 1370
// get_next_line functions
char *get_next_line(int fd);
void *free_resources(char **saved_data, char **read_buffer);
char *read_and_store(int fd, char *saved_data, char *read_buffer);
char *extract_line_to_return(char *saved_data, char *line_to_return);
char *trim_saved_data(char *saved_data);
// helpers
size_t ft_strlen(const char *s);
char *ft_strdup(const char *s);
char *ft_strjoin(char *s1, char *s2);
char *ft_strchr(const char *s, int c);
char *ft_strcpy(char *dest, const char *src);
int ft_strcmp(char *s1, char *s2);
// error printer
void exit_error(char *err, int per);
// parsing utils
void ft_parsing(t_map *map, int argc, char **argv);
int check_extension(char *path);
void check_borders(char *str, t_map *map, int is_first, int is_last);
void check_player_and_coins(char *str, t_map *map);
void check_arguments(int argc, char *argv[]);
void initialize_map(t_map *map);
void check_map(t_map *map, int fd);
char **grid_map(int rows, int fd);
char **copy_map(char **grid, size_t rows, size_t cols);
void find_player(t_map *map, int *x, int *y);
void flood_fill(t_map *map, int x, int y, char **map_copy, int *exit_found, int *coin_found);
void validate_map(t_map *map);
void print_map(char **grid);
// memory management
void free_2dmap(char **grid);
#endif