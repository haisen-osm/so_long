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
	if (strcmp(path + len - 4, ".ber") != 0)
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
		size_t len = strlen(str);

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
int main(int argc, char *argv[])
{
	t_map map;
	int fd;

	check_arguments(argc, argv);
	fd = open(argv[1], O_RDONLY);
	if (fd < 0)
		exit_error(ERR_OPEN, 1);

	initialize_map(&map);
	check_map(&map, fd);
	close(fd);

	if (map.rows < 3 || map.cols < 3)
		exit_error(ERR_INVALID_MAP, 0);
	if (!map.is_valid)
		exit_error(ERR_INVALID_MAP, 0);
	if (map.player != 1 || map.coin == 0 || map.exitDor != 1 || map.extra_char > 0)
		exit_error(ERR_INVALID_MAP, 0);

	map.grid = malloc((sizeof(char *) * map.rows) + 1);
	char *str;
	fd = open(argv[1], O_RDONLY);
	int i = 0;
	while ((str = get_next_line(fd)) != NULL)
	{
		map.grid[i] = str;
		i++;
	}
	map.grid[i] = NULL;
	i = 0;
	int j = 0;
	while (map.grid[i])
	{
		j = 0;
		while (map.grid[i][j])
		{
			printf("%c", map.grid[i][j]);
			j++;
		}
		i++;
	}

	return (0);
}
