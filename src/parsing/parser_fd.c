/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_fd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: samuel <samuel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/14 23:12:33 by samuel            #+#    #+#             */
/*   Updated: 2025/09/22 11:57:46 by samuel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int init_map_storage(t_data *data, char *first_line)
{
    data->pmap->line_count = 1;
    data->pmap->map = malloc(sizeof(char *) * 2);
    if (!data->pmap->map)
    {
        free(first_line);
        return (err_msg("Malloc failed\n", 1), -1);
    }
    data->pmap->map[0] = NULL;
    data->pmap->map[1] = NULL;
    if (valid_char(first_line) == -1)
    {
        free(first_line);
        return (-1);
    }
    data->pmap->map[0] = first_line;
    return (0);
}


int	parse_map_lines(t_data *data, int fd, char *first_line)
{
	char	*line;

	if (init_map_storage(data, first_line) == -1)
		return (-1);
	line = get_next_line(fd);
	while (line)
	{
		if (valid_char(line) == -1)
		{
			free(line);
			free_map_and_textures(data->pmap);
			return (-1);
		}
		if (append_map_line(data, line) == -1)
			return (-1);
		line = get_next_line(fd);
	}
	return (0);
}

int	is_header_complete(t_map *pmap)
{
	if (pmap->no && pmap->so && pmap->we && pmap->ea
		&& pmap->floor[0] && pmap->ceiling[0])
		return (1);
	return (0);
}

int	read_header(t_data *data, int fd, char **first_map_line)
{
	char	*line;
	int		status;

	line = get_next_line(fd);
	if (!line)
		return (err_msg("Empty file\n", 1), -1);
	while (line)
	{
		if (line[0] == '\n' || line[0] == '\0')
		{
			free(line);
			line = get_next_line(fd);
			continue ;
		}
		if (!is_header_complete(data->pmap))
		{
			status = set_header_line(data, &line, fd);
			if (status < 0)
				return (-1);
			continue ;
		}
		*first_map_line = line;
		return (0);
	}
	return (err_msg("No map found\n", 1), -1);
}

int	parse_file(t_data *data, char *file)
{
	int		fd;
	int		status;
	char	*first_map_line;

	fd = open(file, O_RDONLY);
	if (fd < 0)
		return (err_msg("Invalid fd\n", 1), -1);
	first_map_line = NULL;
	status = read_header(data, fd, &first_map_line);
	if (status == -1)
		return (close(fd), -1);
	if (!first_map_line)
		return (close(fd), err_msg("No map found\n", 1), -1);
	if (parse_map_lines(data, fd, first_map_line) == -1)
		return (close(fd), -1);
	close(fd);
	return (0);
}
