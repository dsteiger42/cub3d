#include "../includes/cub3d.h"

int	valid_map_name(char *file)
{
	int	len;

	if (!file)
		return (err_msg("Invalid pointer\n", 1), -1);
	len = ft_strlen(file);
	if (len < 4 || ft_strncmp(&file[len - 4], ".cub", 4) != 0)
		return (err_msg("Map is not a .cub file\n", 1), -1);
	return (0);
}
