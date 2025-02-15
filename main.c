#include "so_long.h"

void	exit_error(char *err, int per)
{
	write(1, "Error\n", 6);
	if (err)
		write(1, err, strlen(err));
	if (per)
		perror("");
	exit(EXIT_FAILURE);
}


int count_dots(char *path)
{
	int i = 0;
	int count = 0;
	while (path[i])
	{
		if (path[i] == '.')
			count++;
		i++;
	}
	return (count);
}

int check_extension(char *path)
{
	int len = strlen(path) - 1;
	if (count_dots(path) == 1 && path[0] == '.')
		return 0;
	while (len >= 0)
	{
		if (path[len] == '.')
			break;
		len--;
	}
	if (strcmp((path + len), EXTENSTION) == 0)
		return 1;
	return 0;
}
// 1111111111111111111111111111111111
// 1E0000000000000C00000C000000000001
// 1010010100100000101001000000010101
// 1010010010101010001001000000010101
// 1P0000000C00C0000000000000000000C1
// 1111111111111111111111111111111111

void	check_arguments(int argc, char *argv[])
{
	if (argc < 2)
		exit_error("not enough arguments.", 0);
	if (argc > 2)
		exit_error("too much arguments.", 0);
	if (!check_extension(argv[1]))
		exit_error("wrong file extension.", 0);
}

typedef struct s_map
{
	size_t rows;
	size_t cols;
	int is_valid;
	int first_row;
	int last_row;
}	t_map;

void check_first_row(char *str, t_map *map)
{
	int i = 0;
	while (str[i])
	{
		if (str[i] != '1' && str[i] != '\n')
			map->is_valid = 0;
		i++;
	}
}

int	main(int argc, char *argv[])
{
	t_map map;
	check_arguments(argc, argv);
	int fd = open(argv[1], O_RDONLY);
	if (fd < 0)
		exit_error(NULL, 1);
	char *str = NULL;
	size_t len = 0;
	int i = 0;
	map.rows = 0;
	while ((str = get_next_line(fd)) != NULL)
	{
		printf("%s",str);
		len = ft_strlen(str);
		if (*str == '\n')
			map.is_valid = 0;
		else if (str[len - 1] == '\n')
		{
			if (i == 0)
				map.cols = len - 1;
			else{
				if (map.cols != len -1)
					map.is_valid = 0;
			}
		}
		else{
			if (i == 0)
				map.cols = len;
			else{
				if (map.cols != len)
					map.is_valid = 0;
			}
		}
		if (i == 0)
			check_first_row(str, &map);
		i++;
		map.rows++;
	}
	if (map.is_valid == 0)
		printf("not valid");
}

//chech the path.
//chech the extension
//open the file
//read line 
// struct structure to check the map borders and player, and coins;
//TODO handle this case when the ".ber" is the name of the file,
//TODO the problem is when i give the full path like this "map/.ber"