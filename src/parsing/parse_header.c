#include "../includes/cub3d.h"

int	assign_texture(char **dst, char *trim, char *id)
{
	if (*dst)
	{
		free(trim);
		return (err_msg("Duplicate texture ", 1), err_msg(id, 0), -1);
	}
	*dst = trim;
	return (0);
}

int	parse_texture(t_map *pmap, char *id, char *path)
{
	char	*trim;

	trim = ft_strtrim(path, " \t\n");
	if (!trim)
		return (err_msg("Malloc failed\n", 1), -1);
	if (!ft_strncmp(id, "NO", 2))
		return (assign_texture(&pmap->no, trim, "NO"));
	if (!ft_strncmp(id, "SO", 2))
		return (assign_texture(&pmap->so, trim, "SO"));
	if (!ft_strncmp(id, "WE", 2))
		return (assign_texture(&pmap->we, trim, "WE"));
	if (!ft_strncmp(id, "EA", 2))
		return (assign_texture(&pmap->ea, trim, "EA"));
	free(trim);
	return (err_msg("Invalid texture ID\n", 1), -1);
}

int	parse_color_line(int *arr, char *line)
{
	char	**split;
	int		i;

	if (arr[0])
		return (err_msg("Duplicate color definition\n", 1), -1);
	split = ft_split(line, ',');
	if (!split)
		return (err_msg("Malloc failed\n", 1), -1);
	i = 0;
	while (split[i])
	{
		if (is_number_invalid(split[i]))
			return (ft_free_split(split), err_msg("Invalid RGB\n", 1), -1);
		arr[i] = ft_atoi(split[i]);
		if (arr[i] < 0 || arr[i] > 255)
			return (ft_free_split(split), err_msg("Invalid RGB\n", 1), -1);
		i++;
	}
	ft_free_split(split);
	if (i != 3)
		return (err_msg("RGB needs 3 values\n", 1), -1);
	return (0);
}

int	parse_header_line(t_map *pmap, char *line)
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
	return (1);
}

int	set_header_line(t_data *data, char **line_ptr, int fd)
{
	char	*line;
	int		status;

	line = *line_ptr;
	if (!line)
		return (0);
	status = parse_header_line(data->pmap, line);
	if (status == 0)
	{
		free(line);
		*line_ptr = get_next_line(fd);
		return (0);
	}
	if (status)
	{
		free(line);
		free_map_and_textures(data->pmap);
		err_msg("Invalid header\n", 1);
		return (-1);
	}
	return (0);
}
