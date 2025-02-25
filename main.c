#include "so_long.h"

void exit_error(char *err, int per)
{
	write(2, "Error\n", 6);
	if (err)
		write(2, err, ft_strlen(err));
	if (per)
		perror("");
	exit(EXIT_FAILURE);
}

int check_extension(char *path)
{
	int len = ft_strlen(path);

	if (len < 5)
		return (0);
	if (ft_strcmp(path + len - 4, ".ber") != 0)
		return (0);
	int i = len - 5;
	while (i >= 0)
	{
		if (path[i] == '/')
			return (i < len - 5);
		i--;
	}
	return (1);
}

void check_borders(char *str, t_map *map, int is_first, int is_last)
{
	int i = 0;

	while (str[i] && str[i] != '\n')
	{
		if ((is_first || is_last) && str[i] != '1')
			map->is_valid = 0;
		else if ((i == 0 || i == map->cols - 1) && str[i] != '1')
			map->is_valid = 0;
		i++;
	}
}

void check_player_and_coins(char *str, t_map *map)
{
	int i;
	i = 0;
	while (str[i] && str[i] != '\n')
	{
		if (str[i] == 'P')
			map->player++;
		else if (str[i] == 'C')
			map->coin++;
		else if (str[i] == 'E')
			map->exitDoor++;
		else if (str[i] != '0' && str[i] != '1')
			map->extra_char++;
		i++;
	}
}

void check_arguments(int argc, char *argv[])
{
	if (argc != 2)
		exit_error(ERR_ARGS, 0);
	if (!check_extension(argv[1]))
		exit_error(ERR_EXT, 0);
}

void initialize_map(t_map *map)
{
	map->rows = 0;
	map->is_valid = 1;
	map->player = 0;
	map->coin = 0;
	map->exitDoor = 0;
	map->extra_char = 0;
}

void check_map(t_map *map, int fd)
{
	int i = 0;
	char *str;

	while ((str = get_next_line(fd)) != NULL)
	{
		int len = ft_strlen(str);
		if (len == 1 && str[0] == '\n')
			exit_error(ERR_EMPTY_LINE, 0);
		if (map->rows == 0)
			map->cols = (str[len - 1] == '\n') ? len - 1 : len;
		else if (map->cols != ((str[len - 1] == '\n') ? len - 1 : len))
			map->is_valid = 0;
		check_borders(str, map, i == 0, str[len - 1] == '\0');
		check_player_and_coins(str, map);
		free(str);
		map->rows++;
		i++;
	}
}

char **grid_map(int rows, int fd)
{
	char *str;
	char **arr = malloc(sizeof(char *) * (rows + 1));
	int i = 0;

	while (i < rows && (str = get_next_line(fd)) != NULL)
	{
		arr[i] = str;
		i++;
	}
	arr[i] = NULL;
	return arr;
}

char **copy_map(char **grid, size_t rows, size_t cols)
{
	char **copy;
	size_t i;
	(void)cols;
	copy = malloc(sizeof(char *) * (rows + 1));
	if (!copy)
		return (NULL);
	i = 0;
	while (i < rows)
	{
		copy[i] = (char *)malloc(sizeof(char) * (ft_strlen(grid[i]) + 1));
		if (!copy[i])
		{
			while (i > 0)
				free(copy[--i]);
			free(copy);
			return (NULL);
		}
		ft_strcpy(copy[i], grid[i]);
		i++;
	}
	copy[i] = NULL;
	return (copy);
}

void find_player(t_map *map, int *row, int *col)
{
	int i = 0, j;
	while (i < map->rows)
	{
		j = 0;
		while (map->grid[i][j])
		{
			if (map->grid[i][j] == 'P')
			{
				*row = i;
				*col = j;
				return;
			}
			j++;
		}
		i++;
	}
}
void find_door(t_map *map, int *row, int *col)
{
	int i = 0, j;
	while (i < map->rows)
	{
		j = 0;
		while (map->grid[i][j])
		{
			if (map->grid[i][j] == 'E')
			{
				*row = i;
				*col = j;
				return;
			}
			j++;
		}
		i++;
	}
}

void flood_fill(t_map *map, int row, int col, char **map_copy, int *exit_found, int *coin_found)
{
	if (row < 0 || col < 0 || row >= map->rows || col >= map->cols)
		return;
	if (map_copy[row][col] == '1' || map_copy[row][col] == 'V')
		return;
	if (map_copy[row][col] == 'C')
		(*coin_found)++;
	if (map_copy[row][col] == 'E')
		(*exit_found) = 1;
	map_copy[row][col] = 'V';
	flood_fill(map, row + 1, col, map_copy, exit_found, coin_found);
	flood_fill(map, row - 1, col, map_copy, exit_found, coin_found);
	flood_fill(map, row, col + 1, map_copy, exit_found, coin_found);
	flood_fill(map, row, col - 1, map_copy, exit_found, coin_found);
}

void validate_map(t_map *map)
{
	int row, col;
	find_player(map, &row, &col);
	int exit_found = 0;
	int coin_found = 0;
	flood_fill(map, row, col, map->grid_copy, &exit_found, &coin_found);
	if (coin_found != map->coin || exit_found != 1)
		exit_error(ERR_NOT_REACHABLE, 0);
}

void free_2dmap(char **grid)
{
	int i = 0;
	while (grid[i])
	{
		free(grid[i]);
		i++;
	}
	free(grid);
}

void my_mlx_img(t_game *game, void *img, int x, int y)
{
	int mlx_img = mlx_put_image_to_window(game->mlx, game->win, img, x, y);
	if (!mlx_img)
		exit(EXIT_FAILURE);
}

void map_rendering(t_game *game)
{
	int i = 0, j = 0;
	int xx = 0, yy = 0;
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

int close_game(t_game *game)
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
	if (game->win)
		mlx_destroy_window(game->mlx, game->win);
	if (game->mlx)
	{
		mlx_destroy_display(game->mlx);
		free(game->mlx);
	}
	if (game->map)
	{
		if (game->map->grid)
			free_2dmap(game->map->grid);
	}
	exit(0);
	return 0;
}

void ft_parsing(t_map *map, int argc, char **argv)
{
	int fd;

	check_arguments(argc, argv);
	fd = open(argv[1], O_RDONLY);
	if (fd < 0)
		exit_error(ERR_OPEN, 1);
	initialize_map(map);
	check_map(map, fd);
	close(fd);
	if (map->rows < 3 || map->cols < 3)
		exit_error(ERR_INVALID_MAP, 0);
	if (!map->is_valid)
		exit_error(ERR_INVALID_MAP, 0);
	if (map->player != 1 || map->coin == 0 || map->exitDoor != 1 || map->extra_char > 0)
		exit_error(ERR_INVALID_MAP, 0);

	fd = open(argv[1], O_RDONLY);
	map->grid = grid_map(map->rows, fd);
	map->grid_copy = copy_map(map->grid, map->rows, map->cols);
	validate_map(map);
	close(fd);
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
	int x = 64, y = 64;
	game->player = mlx_xpm_file_to_image(game->mlx, "textures/player.xpm", &x, &y);
	if (!game->player)
		exit(EXIT_FAILURE);
	game->diamond = mlx_xpm_file_to_image(game->mlx, "textures/diamond.xpm", &x, &y);
	if (!game->diamond)
		exit(EXIT_FAILURE);
	game->wall = mlx_xpm_file_to_image(game->mlx, "textures/wall.xpm", &x, &y);
	if (!game->wall)
		exit(EXIT_FAILURE);
	game->grass = mlx_xpm_file_to_image(game->mlx, "textures/stone.xpm", &x, &y);
	if (!game->grass)
		exit(EXIT_FAILURE);
	game->broke_door = mlx_xpm_file_to_image(game->mlx, "textures/closed_exit.xpm", &x, &y);
	if (!game->broke_door)
		exit(EXIT_FAILURE);
	game->open_door = mlx_xpm_file_to_image(game->mlx, "textures/open_exit.xpm", &x, &y);
	if (!game->open_door)
		exit(EXIT_FAILURE);
	game->collected_coins = 0;
	game->moves_count = 0;
}
void print_moves(char *str, int count)
{
	ft_putstr(str);
	ft_putnbr(count);
	ft_putstr("\n");
}
void move_player(t_game *game, int row_delta, int col_delta)
{
	int row = 0, col = 0, drow = 0, dcol = 0;
	find_player(game->map, &row, &col);
	find_door(game->map, &drow, &dcol);
	int new_row = row + row_delta;
	int new_col = col + col_delta;

	if (new_row < 0 || new_row >= game->map->rows ||
		new_col < 0 || new_col >= game->map->cols)
		return;
	if (game->map->coin == game->collected_coins)
		mlx_put_image_to_window(game->mlx, game->win, game->open_door, dcol * 64, drow * 64);
	if (game->map->grid[new_row][new_col] == '1')
		return;
	if (game->map->grid[new_row][new_col] == 'C')
	{
		game->collected_coins++;
		if (game->map->coin == game->collected_coins)
			mlx_put_image_to_window(game->mlx, game->win, game->open_door, dcol * 64, drow * 64);
	}
	if (game->map->grid[new_row][new_col] == 'E' &&
		game->map->coin == game->collected_coins)
	{
		ft_putstr("You won!\n");
		close_game(game);
	}
	if (game->map->grid[new_row][new_col] == 'E' &&
		game->map->coin != game->collected_coins)
		return;
	mlx_put_image_to_window(game->mlx, game->win, game->grass, col * 64, row * 64);
	mlx_put_image_to_window(game->mlx, game->win, game->player, new_col * 64, new_row * 64);
	game->map->grid[new_row][new_col] = 'P';
	game->map->grid[row][col] = '0';
	game->moves_count++;
	print_moves("mouvements count: ", game->moves_count);
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
	else if (keycode == XK_Escape)
		close_game(game);
	return (0);
}

int main(int argc, char *argv[])
{
	t_map map;
	t_game game;

	ft_parsing(&map, argc, argv);
	free_2dmap(map.grid_copy);
	game_init(&map, &game);
	map_rendering(&game);
	mlx_key_hook(game.win, key_hook, &game);
	mlx_hook(game.win, 17, 0, close_game, &game);
	mlx_loop(game.mlx);
	return (0);
}
