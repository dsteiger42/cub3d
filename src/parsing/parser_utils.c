#include "../includes/cub3d.h"

int	valid_char(char *line)
{
	int	x;

	x = 0;
	while (line[x])
	{
		if (!ft_strchr("01NSEW \t\v\r\f\n", line[x]))
			return (err_msg("Invalid character in map\n", 1), -1);
		x++;
	}
	return (0);
}

int open_and_check(char *path)
{
    int fd;

    fd = open(path, O_RDONLY);
    if (fd < 0)
        return (err_msg("Texture file not found\n", 1), -1);
    close(fd);
    return (0);
}

char	**ft_realloc(char **map, int new_size)
{
	char	**new_map;
	int		i;

	new_map = malloc(sizeof(char *) * (new_size + 1));
	if (!new_map)
		return (NULL);
	i = 0;
	while (i < new_size && map && map[i])
	{
		new_map[i] = map[i];
		i++;
	}
	if (map)
		free(map);
	new_map[new_size] = NULL;
	return (new_map);
}