/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vgotzlov <vgotzlov@student.42prague.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/10 13:20:52 by vgotzlov          #+#    #+#             */
/*   Updated: 2025/08/21 19:36:20 by vgotzlov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

#include <stdio.h>

char	*get_next_line(int fd)
{
	int			bytes_read;
	char		*small_buffer;
	static int	count;

	count = 1;
	printf("ft_calloc#[%d]---", count++);
	small_buffer = ft_calloc(BUFFER_SIZE + 1, sizeof(char));
	if (small_buffer == NULL)
		return (NULL);
	bytes_read = read(fd, small_buffer, BUFFER_SIZE);
	if (bytes_read <= 0)
	{
		free (small_buffer);
		return (NULL);
	}
	return (small_buffer);
}

int	main(void)
{
	int		fd;
	char	*next_line;
	int		count;

	count = 0;
	fd = open("example.txt", O_RDONLY);
	if (fd == -1)
	{
		printf("Error opening file");
		return (1);
	}
	while (1)
	{
		next_line = get_next_line(fd);
		if (next_line == NULL)
			break ;
		count++;
		printf("[%d]:%s\n", count, next_line);
		free(next_line);
		next_line = NULL;
	}
	close(fd);
	return (0);
}
