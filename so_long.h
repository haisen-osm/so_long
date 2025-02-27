/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okhourss <okhourss@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/15 13:09:28 by okhourss          #+#    #+#             */
/*   Updated: 2025/02/27 21:06:59 by okhourss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_LONG_H
#define SO_LONG_H

#include "minilibx-linux/mlx.h"
#include <X11/keysym.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
// #include <mlx.h>

typedef struct s_map
{
	int rows;
	int cols;
	int is_valid;
	int player;
	int coin;
	int exit_door;
	int extra_char;
	char **grid;
	char **grid_copy;
	int door_col;
	int door_row;
} t_map;

typedef struct s_game
{
	void *mlx;
	void *win;
	t_map *map;
	void *player;
	void *grass;
	void *diamond;
	void *wall;
	void *open_door;
	void *broke_door;
	int collected_coins;
	int moves_count;
} t_game;

typedef struct s_position
{
	int row;
	int col;
} t_position;

typedef struct s_flood
{
	int exit_found;
	int coin_found;
	int row;
	int col;
} t_flood;

#define EXTENSTION ".ber"
#define ERR_ARGS "Invalid number of arguments\n"
#define ERR_EXT "Wrong file extension. Expected '.ber'\n"
#define ERR_OPEN "Failed to open the file\n"
#define ERR_EMPTY_LINE "Empty line detected in the map\n"
#define ERR_INVALID_MAP "Invalid map structure\n"
#define ERR_NOT_REACHABLE "Not all collectibles are reachable\n"
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
void ft_putstr(char *str);
void ft_putnbr(int n);
void ft_putchar(char c);
// clean and exit
void exit_error(char *err, t_game *game, char *str, char **arr);
void free_2dmap(char **grid);
int close_game(t_game *game, int status);
// checkers
int check_extension(char *path);
void check_borders(char *str, t_map *map, int is_first, int is_last);
void check_player_and_coins(char *str, t_map *map);
void check_arguments(int argc, char *argv[]);
void check_map(t_map *map, int fd);
// game rendering
void my_mlx_img(t_game *game, void *img, int x, int y);
void map_rendering(t_game *game);
// initializing
void ini_game(t_game *game);
void initialize_map(t_map *map);
void xpm_to_image(void **img, t_game *game, char *path);
void game_init(t_map *map, t_game *game);
// parsing utils
void find_player(t_map *map, int *row, int *col);
void flood_fill(t_map *map, t_flood *flood, int col, int row);
char **grid_map(int rows, int fd);
char **copy_map(char **grid, size_t rows, size_t cols);
void validate_map(t_map *map);
void ft_parsing(t_map *map, int argc, char **argv);
// player mov
void find_door(t_map *map);
void print_moves(char *str, int count);
void move_player(t_game *game, int row_delta, int col_delta);
int key_hook(int keycode, void *param);
#endif