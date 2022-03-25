/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csantivi <csantivi@student.42bangkok.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/22 17:05:16 by csantivi          #+#    #+#             */
/*   Updated: 2022/03/22 23:16:22 by csantivi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

char	*read_and_collect(int fd, char *current)
{
	char	*buff;
	int		readed;

	buff = malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!buff)
		return (NULL);
	readed = 1;
	while (!found_newline(current) && readed != 0)
	{
		readed = read(fd, buff, BUFFER_SIZE);
		if (readed == -1)
		{
			free(buff);
			return (NULL);
		}
		buff[readed] = '\0';
		current = collect(current, buff);
	}
	free(buff);
	return (current);
}

char	*get_next_line(int fd)
{
	static char	*current[10240];
	char		*line;

	if (fd < 0 || BUFFER_SIZE <= 0 || fd > 10240)
		return (NULL);
	current[fd] = read_and_collect(fd, current[fd]);
	if (!current[fd])
		return (NULL);
	line = get_line(current[fd]);
	current[fd] = new_current(current[fd]);
	return (line);
}
