
#include "cub3d.h"

void	get_map_textures(t_data *data)
{
	char	**splited;
	int		i;

	i = 0;
	while (i < 4)
	{
		splited = ft_split(data->file_content[i++], ", \n");
		if (!splited[0])
			return ;
		if (ft_strcmp(splited[0], NORTH_TEXTURE) == EQUAL)
			data->map.north_texture = ft_strdup(splited[1]);
		else if (ft_strcmp(splited[0], SOUTH_TEXTURE) == EQUAL)
			data->map.south_texture = ft_strdup(splited[1]);
		else if (ft_strcmp(splited[0], EAST_TEXTURE) == EQUAL)
			data->map.east_texture = ft_strdup(splited[1]);
		else if (ft_strcmp(splited[0], WEST_TEXTURE) == EQUAL)
			data->map.west_texture = ft_strdup(splited[1]);
		free_split(splited);
	}
	if (open(data->map.north_texture, O_RDONLY) < 0
		|| open(data->map.south_texture, O_RDONLY) < 0
		|| open(data->map.east_texture, O_RDONLY) < 0
		|| open(data->map.west_texture, O_RDONLY) < 0)
		ft_puterror("Texture doesn't exist!\n");
}

void	get_rgb(t_color *color, char **str)
{
	color->r = ft_atoi(str[0]);
	color->g = ft_atoi(str[1]);
	color->b = ft_atoi(str[2]);
}

void	get_colors(t_data *ptr)
{
	char	**splited;
	int		i;

	i = 0;
	while (ptr->file_content[i])
	{
		if (ptr->file_content[i][0] == '1'
				|| ptr->file_content[i][0] == ' '
				|| ptr->file_content[i][0] == '0')
			break ;
		splited = ft_split(ptr->file_content[i++], ", \n");
		if (splited[0])
		{
			if (ft_strcmp(splited[0], FLOOR) == EQUAL)
				get_rgb(&ptr->map.floor_color, splited + 1);
			else if (ft_strcmp(splited[0], CEILLING) == EQUAL)
				get_rgb(&ptr->map.ceilling_color, splited + 1);
		}
		free_split(splited);
	}
}

void	get_map(t_data *ptr)
{
	int		i;
	int		j;

	i = 0;
	j = 0;
	ptr->map.row = get_map_len(ptr);
	ptr->map.map = malloc(sizeof(char *) * (ptr->map.row + 1));
	ptr->map.col = 0;
	if (!ptr->map.map)
		ft_puterror("Malloc Error: parser.c: 201\n");
	while (ptr->file_content[i])
	{
		if (ptr->file_content[i][0] == '1'
				|| ptr->file_content[i][0] == ' '
				|| ptr->file_content[i][0] == '0')
		{
			ptr->map.map[j++] = ft_strndup(ptr->file_content[i],
					ft_strlen(ptr->file_content[i]) - \
					check_new_line(ptr->file_content[i]));
			if (ptr->map.col < ft_strlen(ptr->map.map[j - 1]))
				ptr->map.col = ft_strlen(ptr->map.map[j - 1]);
		}
		i++;
	}
	ptr->map.map[j] = 0;
}

void	get_player_pos(t_map *map)
{
	int	row;
	int	col;

	row = 0;
	while (map->map[row])
	{
		col = 0;
		while (map->map[row][col])
		{
			if (in_charset(map->map[row][col], "NSEW"))
			{
				map->player.x = row;
				map->player.y = col;
				map->starting_pos = map->map[row][col];
				return ;
			}
			col++;
		}
		row++;
	}
}
