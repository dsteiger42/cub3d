/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_fd_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: samuel <samuel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/14 23:57:48 by samuel            #+#    #+#             */
/*   Updated: 2025/09/15 13:30:50 by samuel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int	is_number_invalid(char *s)
{
	int	i;

	if (!s)
		return (1);
	i = 0;
	while (s[i] && (s[i] == ' ' || s[i] == '\t'))
		i++;
	if (!s[i])
		return (1);
	while (s[i])
	{
		if (!ft_isdigit(s[i]) && s[i] != ' ' && s[i] != '\t' && s[i] != '\n')
			return (1);
		i++;
	}
	return (0);
}

int	append_map_line(t_data *data, char *line)
{
	int	i;

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
	return (0);
}
