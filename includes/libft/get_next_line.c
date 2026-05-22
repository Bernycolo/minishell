/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bconejo- <bconejo-@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/01 17:20:01 by bconejo-          #+#    #+#             */
/*   Updated: 2026/04/02 13:01:09 by bconejo-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	find_jump(char *str)
{
	int	character;

	if (!str)
		return (-1);
	character = 0;
	while (str[character] && str[character] != '\n')
		character++;
	if (str[character] == '\n')
		return (character);
	else
		return (-1);
}

static char	*get_data(int fd, char *data)
{
	int		n_bytes;
	char	*buffer;
	char	*temp;

	buffer = malloc(BUFFER_SIZE + 1);
	if (!buffer)
		return (NULL);
	n_bytes = 1;
	while (n_bytes > 0 && find_jump(data) == -1)
	{
		n_bytes = read(fd, buffer, BUFFER_SIZE);
		if (n_bytes == 0)
			return (free(buffer), data);
		if (n_bytes < 0)
			return (free(buffer), free(data), NULL);
		buffer[n_bytes] = '\0';
		temp = data;
		data = ft_strjoin(temp, buffer);
		free(temp);
		if (!data)
			return (free(buffer), NULL);
	}
	free(buffer);
	return (data);
}

static char	*clean_data(char *data)
{
	char	*data_clean;
	int		jump;

	if (!data)
		return (NULL);
	jump = find_jump(data);
	if (jump >= 0)
		data_clean = ft_substr(data, 0, jump + 1);
	else
		data_clean = ft_substr(data, 0, ft_strlen(data));
	return (data_clean);
}

static char	*update_data(char *data)
{
	int		jump;
	char	*data_updated;

	if (!data)
		return (NULL);
	jump = find_jump(data);
	data_updated = NULL;
	if (jump >= 0)
		data_updated = ft_substr(data, jump + 1, ft_strlen(data));
	return (free(data), data_updated);
}

char	*get_next_line(int fd)
{
	char		*line;
	static char	*draft_line[MAX_FD];

	if (fd < 0 || BUFFER_SIZE <= 0 || fd >= MAX_FD)
		return (NULL);
	draft_line[fd] = get_data(fd, draft_line[fd]);
	line = clean_data(draft_line[fd]);
	draft_line[fd] = update_data(draft_line[fd]);
	if (line && line[0] == '\0')
		return (free(line), NULL);
	return (line);
}
