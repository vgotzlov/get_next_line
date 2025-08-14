/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vgotzlov <vgotzlov@student.42prague.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/10 13:20:52 by vgotzlov          #+#    #+#             */
/*   Updated: 2025/08/14 14:21:23 by vgotzlov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "get_next_line.h"

#include <stdio.h>

char *get_next_line(int fd)
{
	int		bytes_read;
	char	*small_buffer;

	small_buffer = ft_calloc(3 + 1, sizeof(char));
	if (small_buffer == NULL)
		return (NULL);
	bytes_read = read(fd, small_buffer, 3);
	if (bytes_read <= 0)
		return (NULL);
	return (small_buffer);
}

int main(void)
{
	int		fd;
	char	*next_line;
	int		count;

	count = 0;
	fd = open("example.txt", O_RDONLY);
	next_line = get_next_line(fd);
	count++;
	printf("[%d]:%s\n", count, next_line);
	next_line = NULL;

	close(fd);
	return (0);
}