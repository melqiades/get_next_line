
//#define BUFFER_SIZE 10000000
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
	 if (!*s2)
 		return ((char *)s1);
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
	free((char *)s1);
	//free((char *)s2);
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

int	ft_check_buff(char* buffer, char *new_buffer)
{	
	int	i;

	i = 0;
	if (*new_buffer == 0 && *buffer == 0)
	{	
		free(new_buffer);
		return (-2);
	}
	else if (*new_buffer == 0)
	{
		free (new_buffer);
		return	(ft_strlen(buffer) - 1);
	}
	free(new_buffer);
	if(!buffer[i])
	{
		return (i);
	}
	while(buffer[i])
	{
		if(buffer[i] == '\n')
			return (i);
		i++;
	}
	return (-1);
}

char	*ft_fill_buffer(int	fd)
{
	char	*buffer;
	int	counter;
	int check;

	counter = 0;
	check = 0;
	buffer = ft_calloc(BUFFER_SIZE + 1, sizeof(char));
	check = read(fd, &buffer[counter++], sizeof(char));
	if (check < 0)
	{
		free(buffer);
		return (NULL);
	}
	if (check == 0)
	{
		return (buffer);
	}
	while (counter < BUFFER_SIZE)
	{
		check = read(fd, &buffer[counter], sizeof(char));
		if (check < 0)
		{
			free(buffer);
			return (NULL);
		}
		if (check == 0)
			return (buffer);
		if (buffer[counter] == 0)
			break ;
		counter++;
	}
	buffer[counter] = 0;
	return (buffer);
}

char	*get_next_line(int fd)
{
	static char	*process_buff;
	char	*buffer;
	int		line_index;
	char	*ret;
	char *temp;

	line_index = -1;
	if (process_buff == NULL)
		process_buff = ft_calloc(1, sizeof(char));
	while (line_index <= -1)
	{
		buffer = ft_fill_buffer(fd);
		if(buffer == NULL || line_index == -2)
		{	
			free(buffer);
			return (NULL);
		}
		process_buff = ft_strjoin(process_buff, buffer);
		line_index = ft_check_buff(process_buff, buffer);
	}
	ret = ft_calloc((line_index + 2 ), sizeof(char)); 
	ft_strlcpy(ret, process_buff, line_index + 1);
	temp = ft_strdup(process_buff + (line_index + 1));
	free(process_buff);
	process_buff = temp;
	return (ret);
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

	int bytes_written = fprintf(fp, "01234567890123456789012345678901234567890\n987654321098765432109876543210987654321098\n0123456789012345678901234567890123456789012\n987654321098765432109876543210987654321098\n01234567890123456789012345678901234567890");
	fclose(fp);
	int fd = open("multiple_line_no_nl", O_RDONLY);
	printf("at the begging we run the program\n\n");
	line = get_next_line(fd);
	printf("%s", line);
	line = get_next_line(fd);
	printf("%s", line);
	line = get_next_line(fd);
	printf("%s", line);
	line = get_next_line(fd);
	printf("%s", line);
	line = get_next_line(fd);
	printf("%s", line);
	line = get_next_line(fd);
	printf("%s", line);
	line = get_next_line(fd);
	printf("%s", line);
	free(line);

}*/