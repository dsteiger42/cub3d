#include "../includes/cub3d.h"

static int open_and_check(char *path)
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


static int parse_texture(t_config *config_map, char *id, char *path)
{
    char *trim;

    trim = ft_strtrim(path, " \t\n");
    if (!trim)
        return (err_msg("Malloc failed\n", 1), -1);

    if (!ft_strncmp(id, "NO", 2))
    {
        if (config_map->no)
            return free(trim), err_msg("Duplicate texture NO\n", 1), -1;
        config_map->no = trim;
    }
    else if (!ft_strncmp(id, "SO", 2))
    {
        if (config_map->so)
            return free(trim), err_msg("Duplicate texture SO\n", 1), -1;
        config_map->so = trim;
    }
    else if (!ft_strncmp(id, "WE", 2))
    {
        if (config_map->we)
            return free(trim), err_msg("Duplicate texture WE\n", 1), -1;
        config_map->we = trim;
    }
    else if (!ft_strncmp(id, "EA", 2))
    {
        if (config_map->ea)
            return free(trim), err_msg("Duplicate texture EA\n", 1), -1;
        config_map->ea = trim;
    }
    else
        return free(trim), err_msg("Invalid texture ID\n", 1), -1;

    return open_and_check(trim);
}

static int parse_color_line(int *arr, char *line)
{
    char **split;
    int i;

    // verifica se já foi definido
    if (arr[0])
        return err_msg("Duplicate color definition\n", 1), -1;

    split = ft_split(line, ',');
    if (!split)
        return err_msg("Malloc failed\n", 1), -1;

    i = 0;
    while (split[i])
    {
        arr[i] = ft_atoi(split[i]);
        if (arr[i] < 0 || arr[i] > 255)
            return ft_free_split(split), err_msg("Invalid RGB\n", 1), -1;
        i++;
    }
    ft_free_split(split);
    if (i != 3)
        return err_msg("RGB needs 3 values\n", 1), -1;

    return 0;
}


static int parse_header_line(t_config *config_map, char *line)
{
    if (!ft_strncmp(line, "NO ", 3))
        return parse_texture(config_map, "NO", line + 3);
    if (!ft_strncmp(line, "SO ", 3))
        return parse_texture(config_map, "SO", line + 3);
    if (!ft_strncmp(line, "WE ", 3))
        return parse_texture(config_map, "WE", line + 3);
    if (!ft_strncmp(line, "EA ", 3))
        return parse_texture(config_map, "EA", line + 3);
    if (!ft_strncmp(line, "F ", 2))
        return parse_color_line(config_map->floor, line + 2);
    if (!ft_strncmp(line, "C ", 2))
        return parse_color_line(config_map->ceiling, line + 2);

    return 0;
}


static int	valid_char(char *line)
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

static int	parse_map_lines(t_data *data, int fd, char *first_line)
{
	char	*line;
	int		i;

	data->pmap->line_count = 1;
	data->pmap->map = malloc(sizeof(char *) * 2); 
	if (!data->pmap->map)
		return (err_msg("Malloc failed\n", 1), -1);

	if (valid_char(first_line) == -1)
		return (-1);
	data->pmap->map[0] = first_line;
	data->pmap->map[1] = NULL;
	while ((line = get_next_line(fd)))
	{
		if (valid_char(line) == -1)
		{
			free(line);
			return (-1);
		}
		i = data->pmap->line_count;
		data->pmap->map = ft_realloc(data->pmap->map, i + 1);
		if (!data->pmap->map)
			return (free(line), err_msg("Malloc failed\n", 1), -1);

		data->pmap->map[i] = line;
		data->pmap->line_count++;
		data->pmap->map[data->pmap->line_count] = NULL;
	}
	return (0);
}

int parse_file(t_data *data, char *file)
{
    int fd;
    char *line;
    char *first_map_line = NULL;

    fd = open(file, O_RDONLY);
    if (fd < 0)
        return (err_msg("Invalid fd\n", 1), -1);

    while ((line = get_next_line(fd)))
    {
        if (line[0] == '\n' || line[0] == '\0')
        {
            free(line);
            continue;
        }
        if (!data->config_map->no || !data->config_map->so ||
            !data->config_map->we || !data->config_map->ea ||
            data->config_map->floor[0] == -1 || data->config_map->ceiling[0] == -1)
        {
            if (parse_header_line(data->config_map, line) == -1)
                return (free(line), close(fd), -1);
            free(line);
            continue;
        }
        first_map_line = line;
        print_config_map(data->config_map);
        break;
    }
    if (!first_map_line)
        return (close(fd), err_msg("No map found\n", 1), -1);
    if (parse_map_lines(data, fd, first_map_line) == -1)
        return (close(fd), -1);     
    close(fd);
    return 0;
}


