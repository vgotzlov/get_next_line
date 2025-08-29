/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vgotzlov <vgotzlov@student.42prague.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/10 13:20:52 by vgotzlov          #+#    #+#             */
/*   Updated: 2025/08/29 13:41:18 by vgotzlov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

#include <stdio.h>

static char	*get_line(char *stash)
{
	size_t	i;
	char	*line;

	if (!stash || !stash[0])
		return (NULL);
	i = 0;
	while (stash[i] && stash[i] != '\n')
		i++;
	line = malloc(i + (stash[i] == '\n') + 1);
	if (!line)
		return (NULL);
	i = 0;
	while (stash[i] && stash[i] != '\n')
	{
		line[i] = stash[i];
		i++;
	}
	if (stash[i] == '\n')
		line[i++] = '\n';
	line[i] = '\0';
	return (line);
}

static char	*save_rest(char *stash)
{
	size_t	i;
	size_t	j;
	char	*rest;

	i = 0;
	while (stash[i] && stash[i] != '\n')
		i++;
	if (!stash[i])
		return (free(stash), NULL);
	i++;
	rest = malloc(ft_strlen(stash + i) + 1);
	if (!rest)
		return (free(stash), NULL);
	j = 0;
	while (stash[i])
		rest[j++] = stash[i++];
	rest[j] = '\0';
	free(stash);
	return (rest);
}

char	*get_next_line(int fd)
{
	int			bytes_read;
	char		*buf;
	char		*line;
	static char	*stash;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	buf = ft_calloc(BUFFER_SIZE + 1, sizeof(char));
	if (buf == NULL)
		return (NULL);
	bytes_read = 1;
	while (bytes_read > 0 && !ft_strchr(stash, '\n'))
	{
		bytes_read = read(fd, buf, BUFFER_SIZE);
		if (bytes_read < 0)
			return (free(buf), free(stash), stash = NULL, NULL);
		buf[bytes_read] = '\0';
		stash = free_join(stash, buf);
	}
	free(buf);
	if (!stash || stash[0] == '\0')
		return ((free(stash), stash = NULL, NULL));
	line = get_line(stash);
	stash = save_rest(stash);
	return (line);
}

char	*free_join(char *s1, const char *s2)
{
	char	*temp;

	if (!s1 && !s2)
		return (NULL);
	temp = ft_strjoin(s1, s2);
	free(s1);
	return (temp);
}

/* int	main(void)
{
	int		fd = open("example.txt", O_RDONLY);
	char	*line;

	while ((line = get_next_line(fd)) != NULL)
	{
		printf("---------------\n");
		printf("%s", line);
		printf("---------------\n");
		free(line);
	}
	close(fd);
	return (0);
}
 */