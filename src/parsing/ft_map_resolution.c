/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_map_resolution.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olabrahm <olabrahm@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/11 22:15:38 by olabrahm          #+#    #+#             */
/*   Updated: 2022/10/12 17:43:47 by olabrahm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	ft_print_map(t_state *state)
{
	int	i;
	int	j;

	i = 0;
	while (i < state->map_height)
	{
		printf("{");
		j = 0;
		while (j < state->map_width)
		{
			if (j == state->map_width - 1)
				printf("'%d' ", state->map[i][j]);
			else
				printf(" '%d', ", state->map[i][j]);
			j++;
		}
		printf("}\n");
		i++;
	}
}

int	ft_found_player(char *line)
{
	int	i;

	i = 0;
	while (line[i])
	{
		if (ft_char_is_player(line[i]))
			return (1);
		i++;
	}
	return (0);
}

int	ft_get_map_width(char **file_content, int lines_len)
{
	int	i;
	int	max;
	int	line_len;

	i = 0;
	max = 0;
	while (i < lines_len)
	{
		line_len = ft_strlen(file_content[i]);
		if (line_len > max)
			max = line_len;
		i++;
	}
	return (max);
}
