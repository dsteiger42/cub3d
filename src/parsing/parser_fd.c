#include "../includes/cub3d.h"

static int parse_texture(t_map *pmap, char *id, char *path)
{
    char *trim;

    trim = ft_strtrim(path, " \t\n");
    if (!trim)
        return (err_msg("Malloc failed\n", 1), -1);

    if (!ft_strncmp(id, "NO", 2))
    {
        if (pmap->no)
            return free(trim), err_msg("Duplicate texture NO\n", 1), -1;
        pmap->no = trim;
    }
    else if (!ft_strncmp(id, "SO", 2))
    {
        if (pmap->so)
            return free(trim), err_msg("Duplicate texture SO\n", 1), -1;
        pmap->so = trim;
    }
    else if (!ft_strncmp(id, "WE", 2))
    {
        if (pmap->we)
            return free(trim), err_msg("Duplicate texture WE\n", 1), -1;
        pmap->we = trim;
    }
    else if (!ft_strncmp(id, "EA", 2))
    {
        if (pmap->ea)
            return free(trim), err_msg("Duplicate texture EA\n", 1), -1;
        pmap->ea = trim;
    }
    else
        return free(trim), err_msg("Invalid texture ID\n", 1), -1;

    return open_and_check(trim);
}

static int parse_color_line(int *arr, char *line)
{
    char **split;
    int i;

    if (arr[0])
        return err_msg("Duplicate color definition\n", 1), -1;
    split = ft_split(line, ',');
    if (!split)
        return (err_msg("Malloc failed\n", 1), -1);
    i = 0;
    while (split[i])
    {
        arr[i] = ft_atoi(split[i]);
        if (arr[i] < 0 || arr[i] > 255)
            return (ft_free_split(split), err_msg("Invalid RGB\n", 1), -1);
        i++;
    }
    ft_free_split(split);
    if (i != 3)
        return (err_msg("RGB needs 3 values\n", 1), -1);

    return 0;
}

static int parse_header_line(t_map *pmap, char *line)
{
    if (!ft_strncmp(line, "NO ", 3))
        return (parse_texture(pmap, "NO", line + 3));
    if (!ft_strncmp(line, "SO ", 3))
        return (parse_texture(pmap, "SO", line + 3));
    if (!ft_strncmp(line, "WE ", 3))
        return (parse_texture(pmap, "WE", line + 3));
    if (!ft_strncmp(line, "EA ", 3))
        return (parse_texture(pmap, "EA", line + 3));
    if (!ft_strncmp(line, "F ", 2))
        return (parse_color_line(pmap->floor, line + 2));
    if (!ft_strncmp(line, "C ", 2))
        return (parse_color_line(pmap->ceiling, line + 2));
    else
        return (1);
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
	{
		free(first_line);
		return (-1);
	}
	data->pmap->map[0] = first_line;
	data->pmap->map[1] = NULL;
	while ((line = get_next_line(fd)))
	{
		if (valid_char(line) == -1)
		{
			free(line);
			free_map_and_textures(data->pmap);
			return (-1);
		}
		i = data->pmap->line_count;
		data->pmap->map = ft_realloc(data->pmap->map, i + 1);
		if (!data->pmap->map)
		{
			free(line);
			free_map_and_textures(data->pmap);
			return (err_msg("Malloc failed\n", 1), -1);
		}
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
        if (!data->pmap->no || !data->pmap->so ||
            !data->pmap->we || !data->pmap->ea ||
            !data->pmap->floor[0] || !data->pmap->ceiling[0])
        {
            if (parse_header_line(data->pmap, line) == 0)
            {
                free(line);
                continue;
            }
            else
            {
                free(line);
                free_map_and_textures(data->pmap);
                close(fd);
                return (err_msg("Invalid header\n", 1), -1);
            }
        }
        first_map_line = line;
        break;
    }
    if (!first_map_line)
        return (close(fd), err_msg("No map found\n", 1), -1);
    if (parse_map_lines(data, fd, first_map_line) == -1)
        return (close(fd), -1);     
    close(fd);
    return 0;
}


