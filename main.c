#include "so_long.h"

void exit_error(char *err, int per)
{
	write(1, "Error\n", 6);
	if (err)
		write(1, err, ft_strlen(err));
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
		else if ((i == 0 || i == (int)map->cols - 1) && str[i] != '1')
			map->is_valid = 0;

		i++;
	}
}

void check_player_and_coins(char *str, t_map *map)
{
	int i = 0;
	while (str[i] && str[i] != '\n')
	{
		if (str[i] == 'P')
			map->player++;
		else if (str[i] == 'C')
			map->coin++;
		else if (str[i] == 'E')
			map->exitDor++;
		else if (str[i] != '0' && str[i] != '1')
			map->extra_char++;
		i++;
	}
}

void check_arguments(int argc, char *argv[])
{
	if (argc < 2)
		exit_error(ERR_ARGS, 0);
	if (argc > 2)
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
	map->exitDor = 0;
	map->extra_char = 0;
}

void check_map(t_map *map, int fd)
{
	int i = 0;
	char *str;

	while ((str = get_next_line(fd)) != NULL)
	{
		size_t len = ft_strlen(str);

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

	copy = (char **)malloc(sizeof(char *) * rows);
	if (!copy)
		return (NULL);
	i = 0;
	while (i < rows)
	{
		copy[i] = (char *)malloc(sizeof(char) * (cols + 1));
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

void find_player(t_map *map, int *x, int *y)
{
	int i = 0;
	int j;
	while (i < (int)map->rows)
	{
		j = 0;
		while (map->grid[i][j])
		{
			if (map->grid[i][j] == 'P')
			{
				*x = i;
				*y = j;
				return;
			}
			j++;
		}
		i++;
	}
}

void flood_fill(t_map *map, int x, int y, char **map_copy, int *exit_found, int *coin_found)
{
	if (x < 0 || y < 0 || x >= (int)map->rows || y >= (int)map->cols)
		return;
	if (map_copy[x][y] == '1' || map_copy[x][y] == 'V')
		return;
	if (map_copy[x][y] == 'C')
		(*coin_found)++;
	if (map_copy[x][y] == 'E')
		(*exit_found) = 1;
	map_copy[x][y] = 'V';
	flood_fill(map, x + 1, y, map_copy, exit_found, coin_found);
	flood_fill(map, x - 1, y, map_copy, exit_found, coin_found);
	flood_fill(map, x, y + 1, map_copy, exit_found, coin_found);
	flood_fill(map, x, y - 1, map_copy, exit_found, coin_found);
}

void validate_map(t_map *map)
{
	int x, y;
	find_player(map, &x, &y);
	int exit_found = 0;
	int coin_found = 0;
	flood_fill(map, x, y, map->grid_copy, &exit_found, &coin_found);
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
void print_map(char **grid)
{
	int i = 0;
	int j = 0;
	while (grid[i])
	{
		j = 0;
		while (grid[i][j])
		{
			printf("%c", grid[i][j]);
			j++;
		}
		i++;
	}
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
	if (map->player != 1 || map->coin == 0 || map->exitDor != 1 || map->extra_char > 0)
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
	game->win = mlx_new_window(game->mlx, game->map->cols * 32, game->map->rows * 32, GAME_TITLE);
	if (!game->win)
		exit_error(ERR_MLX_FAILED, 0);
	int x = 32;
	int y = 32;
	game->player = mlx_xpm_file_to_image(game->mlx, "textures/playerTrab.xpm", &x, &y);
	if (!game->player)
		exit(EXIT_FAILURE);
	game->diamond = mlx_xpm_file_to_image(game->mlx, "textures/diamondTrab.xpm", &x, &y);
	if (!game->diamond)
		exit(EXIT_FAILURE);
	game->wall = mlx_xpm_file_to_image(game->mlx, "textures/wall.xpm", &x, &y);
	if (!game->wall)
		exit(EXIT_FAILURE);
	game->grass = mlx_xpm_file_to_image(game->mlx, "textures/trab.xpm", &x, &y);
	if (!game->grass)
		exit(EXIT_FAILURE);
	game->door = mlx_xpm_file_to_image(game->mlx, "textures/door.xpm", &x, &y);
	if (!game->door)
		exit(EXIT_FAILURE);
}

void my_mlx_img(t_game *game, void *img, int x, int y)
{
	int mlx_img = mlx_put_image_to_window(game->mlx, game->win, img, x, y);
	if (!mlx_img)
		exit(EXIT_FAILURE);
}

void map_rendering(t_game *game)
{
	size_t i = 0, j = 0;
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
				my_mlx_img(game, game->door, xx, yy);
			xx += 32;
			j++;
		}
		yy += 32;
		i++;
	}
}

int key_hook(int keycode, void *param)
{
	// (void)param;
	t_game *game = (t_game *)param;
	printf("%d\n", game->player_y);
	if (keycode == 119)
	{

		printf("UP\n");
		(game->player_y)++;
	}

	// 	else if (keycode == 97)
	// else if (keycode == 100)
	// 	printf("RIGHT\n");
	// else if (keycode == 115)
	// 	printf("DOWN\n");

	return (0);
}

int main(int argc, char *argv[])
{
	t_map map;
	t_game game;
	ft_parsing(&map, argc, argv);
	// print_map(map.grid);
	free_2dmap(map.grid_copy);
	game_init(&map, &game);
	map_rendering(&game);

	mlx_key_hook(game.win, key_hook, &game);
	mlx_loop(game.mlx);
	return (0);
}
