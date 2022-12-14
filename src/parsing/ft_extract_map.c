/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_extract_map.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olabrahm <olabrahm@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/10 21:40:39 by dar_sefriou       #+#    #+#             */
/*   Updated: 2022/10/16 09:43:45 by olabrahm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	has_no_ones(char *line)
{
	int	i;

	i = 0;
	while (line[i])
	{
		if (line[i] == '1')
			return (0);
		i++;
	}
	return (1);
}

static int	ft_invalid_map_line(char **file_content, int line_index)
{
	int	i;

	if (has_no_ones(file_content[line_index]))
		return (1);
	i = 0;
	while (file_content[line_index][i])
	{
		if (ft_invalid_char(file_content[line_index][i])
			|| ft_invalid_surroundings(file_content, line_index, i)
		)
			return (1);
		i++;
	}
	return (0);
}

static int	ft_check_correct_map2(char **file_content, int *i, int *reached_end)
{
	if (ft_strlen(file_content[*i]) == 0)
	{
		*reached_end = 1;
		(*i)++;
		return (1);
	}
	else if (*reached_end || ft_invalid_map_line(file_content, *i))
		ft_exit_error("Error", EXIT_FAILURE);
	return (0);
}

static int	ft_check_correct_map(char **file_content, int lines_len)
{
	int	i;
	int	player_found;
	int	reached_end;

	i = 0;
	player_found = 0;
	reached_end = 0;
	while (i < lines_len)
	{
		if (ft_check_correct_map2(file_content, &i, &reached_end))
			continue ;
		if (ft_found_player(file_content[i]))
		{
			if (player_found)
				ft_exit_error("Error", EXIT_FAILURE);
			player_found = 1;
		}
		i++;
	}
	if (!player_found)
		ft_exit_error("Error", EXIT_FAILURE);
	return (1);
}

void	ft_extract_map(char **file_content, int lines_len, t_state *state)
{
	if (!file_content || !file_content[0] || lines_len <= 1)
		ft_exit_error("Error", EXIT_FAILURE);
	ft_check_correct_map(file_content, lines_len);
	state->map_width = ft_get_map_width(file_content, lines_len);
	state->map_height = lines_len;
	ft_fill_map(file_content, state);
}
