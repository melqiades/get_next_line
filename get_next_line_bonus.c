/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpesan <lpesan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/31 18:38:21 by lpesan            #+#    #+#             */
/*   Updated: 2024/03/31 21:10:35 by lpesan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

char	*fr_joifree(char *buffer, char *buf)
{
	char	*temp;

	temp = ft_strjoin(buffer, buf);
	free(buffer);
	return (temp);
}

char	*ft_next_buffer(char *buffer)
{
	int		i;
	int		j;
	char	*line;

	i = 0;
	while (buffer[i] && buffer[i] != '\n')
		i++;
	if (!buffer[i])
	{
		free(buffer);
		return (NULL);
	}
	line = ft_calloc((ft_strlen(buffer) - i + 1), sizeof(char));
	i++;
	j = 0;
	while (buffer[i])
		line[j++] = buffer[i++];
	free(buffer);
	return (line);
}

char	*ft_get_line(char *buffer)
{
	char	*line;
	int		i;

	i = 0;
	if (!buffer[i])
		return (NULL);
	while (buffer[i] && buffer[i] != '\n')
		i++;
	line = ft_calloc(i + 2, sizeof(char));
	i = 0;
	while (buffer[i] && buffer[i] != '\n')
	{
		line[i] = buffer[i];
		i++;
	}
	if (buffer[i] && buffer[i] == '\n')
		line[i++] = '\n';
	return (line);
}

char	*ft_read_file(int fd, char *res)
{
	char	*buffer;
	int		byte_read;

	if (!res)
		res = ft_calloc(1, 1);
	buffer = ft_calloc(BUFFER_SIZE + 1, sizeof(char));
	byte_read = 1;
	while (byte_read > 0)
	{
		byte_read = read(fd, buffer, BUFFER_SIZE);
		if (byte_read < 0)
		{
			free(buffer);
			free(res);
			return (NULL);
		}
		buffer[byte_read] = 0;
		res = fr_joifree(res, buffer);
		if (res == NULL)
			return (NULL);
		if (ft_strchr(buffer, '\n'))
			break ;
	}
	free(buffer);
	return (res);
}

char	*get_next_line(int fd)
{
	static char	*buffer[4096];
	char		*line;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	buffer[fd] = ft_read_file(fd, buffer[fd]);
	if (!buffer[fd])
		return (NULL);
	line = ft_get_line(buffer[fd]);
	buffer[fd] = ft_next_buffer(buffer[fd]);
	return (line);
}

/*
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>


int main() {
    char *line;
    int fd = 0; // File descriptor for standard input

    printf("Enter text (press Ctrl+D to end):\n");

    // Read lines from standard input using get_next_line
    while ((line = get_next_line(fd)) != NULL) {
        printf("Read from stdin: %s\n", line);
        free(line); // Free the memory allocated for the line
    }

    return 0;
}
// int main()
// {
// 	char	*line;
// // Open the file in write mode ("w")
// 	FILE *fp = fopen("hello.txt", "w");

// 	// Check if the file was opened successfully
	
// 	if (fp == NULL) {
// 		perror("Error opening file");
// 		return 1;
// 	}

// 	// Write the text "hello" to the file

// 	int bytes_written = fprintf(fp, "012345678901234567890");
// 	fclose(fp);
// 	int fd = open("./tests/multiple_nlx5", O_RDONLY);
// 	printf("at the begging we run the program\n\n");


// 	line = get_next_line(fd);
// 	printf("1%s", line);
// 	free(line);
// 	line = get_next_line(fd);
// 	printf("2%s", line);
// 	free(line);
// 	// line = get_next_line(fd);
// 	// printf("3%s", line);
// 	// free(line);
// 	// line = get_next_line(fd);
// 	// printf("4%s", line);
// 	// free(line);
// 	// line = get_next_line(fd);
// 	// printf("5%s", line);
// 	// free(line);
// 	// line = get_next_line(fd);
// 	// printf("6%s", line);
// 	// free(line);
// 	// line = get_next_line(fd);
// 	// printf("7%s", line);
// 	// free(line);

// }*/