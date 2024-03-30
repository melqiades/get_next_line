
//#define BUFFER_SIZE 1
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>
//#include "get_next_line.h"

size_t	ft_strlen(const char *s)
{
	size_t	i;

	i = 0;
	if(s == NULL)
		return (0);
	while (s[i])
		i++;
	return (i);
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	int		i;
	int		j;
	char	*res;

	i = 0;
	j = 0;
	if (!s1 || !s2)
		return (NULL);
	 //if (!*s2)
 		//return ((char *)s1);
	res = malloc((ft_strlen(s1) + ft_strlen(s2) + 1) * sizeof(char));
	while (s1[i])
	{
		res[i] = s1[i];
		i++;
	}
	while (s2[j])
	{
		res[i] = s2[j];
		i++;
		j++;
	}
	res[i] = 0;
	return (res);
}

char	*ft_strdup(const char *s)
{
	char	*ptr;
	int		i;

	i = 0;
	ptr = malloc((ft_strlen(s) + 1) * sizeof(char));
	if (ptr == NULL)
		return (NULL);
	while (s[i])
	{
		ptr[i] = s[i];
		i++;
	}
	ptr[i] = 0;
	return (ptr);
}

void	*ft_calloc(size_t nitems, size_t size)
{
	void	*ptr;
	size_t	i;

	i = 0;
	if (nitems == 0 || size == 0)
		return (malloc(0));
	i = nitems * size;
	if (i / nitems != size)
		return (NULL);
	i = 0;
	ptr = malloc(nitems * size);
	if (ptr == NULL)
		return (NULL);
	while (i < (nitems * size))
	{
		((char *)ptr)[i] = 0;
		i++;
	}
	return (ptr);
}

size_t	ft_strlcpy(char *dst, const char *src, size_t size)
{
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	while (src[j])
	{
		j++;
	}
	if (size != 0)
	{
		while (src[i] != 0 && (i <= size - 1))
		{
			dst[i] = src[i];
			i++;
		}
		dst[i] = 0;
	}
	return (j);
}


int	check_buffer(char *buffer)
{
	int 	end_new_check;
	int 	i;

	end_new_check = 0;
	i = 0;
	while (buffer[i])
	{
		if (buffer[i] == '\n')
		{
			end_new_check = 1;
			break;
		}
		i++;
	}
	return(end_new_check);
}
char	*process_buffer(char *buffer, int offset)
{
	char *new_line;

	new_line = ft_strdup(buffer  + offset);
	free (buffer);
	return (new_line);
}
char	*process_line(char *line)
{
	while(*line && *line != '\n')
		line++;
	if (*line == '\n')
		return (line);
	return (NULL);
}
char *ft_joifree(char *line, char *buffer)
{
	char *res;

	res = ft_strjoin(line, buffer);
	free(line);
	return(res);
}
char	*get_buffer(char *line)
{
	int	counter;
	char	*res;

	counter = 0;
	while (line[counter] && line[counter] != '\n')
		counter++;
	res = ft_strdup(line + counter + 1);
	return(res);
}
char *get_clean_line(char *line)
{
	int	counter;
	char	*res;

	counter = 0;
	while (line[counter] && line[counter] != '\n')
		counter++;
	line[counter + 1] = 0;
	res = ft_strdup(line);
	free(line);
	return(res);
}
char	*get_line(int fd, char *buffer)
{
	char	*line;
	int	bytes_read;
	
	if(!buffer)
		buffer = ft_calloc(BUFFER_SIZE + 1, sizeof(char));
	line = ft_calloc(1, sizeof(char));
	line = ft_joifree(line, buffer);
	bytes_read = 1;
	while(bytes_read > 0)
	{
		bytes_read = read(fd, buffer, BUFFER_SIZE);
		if(bytes_read < 0)
		{	
			free(buffer);
			return (NULL);
		}
		*(buffer + bytes_read) = 0;
		line = ft_joifree(line, buffer);
		if (process_line(buffer))
			break;
	}
	free(buffer);
	return (line);
}

char	*get_next_line(int fd)
{
	char *line;
	static char *buffer;

	if(fd < 0 || BUFFER_SIZE <= 0 || read(fd, 0, 0) < 0)
		return(NULL);
	
	line = get_line(fd, buffer);
	if (!*(line))
		return (NULL);
	buffer = get_buffer(line);
	line = get_clean_line(line);

	return(line);
}

/*
int main()
{
	char	*line;
// Open the file in write mode ("w")
	FILE *fp = fopen("hello.txt", "w");

	// Check if the file was opened successfully
	
	if (fp == NULL) {
		perror("Error opening file");
		return 1;
	}

	// Write the text "hello" to the file

	int bytes_written = fprintf(fp, "");
	fclose(fp);
	int fd = open("hello.txt", O_RDONLY);
	printf("at the begging we run the program\n\n");
	line = get_next_line(fd);
	printf("1%s", line);
	free(line);
	line = get_next_line(fd);
	printf("2%s", line);
	free(line);
	line = get_next_line(fd);
	printf("2%s", line);
	free(line);
}*/