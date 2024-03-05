
#define BUFFER_SIZE 10
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>
//#include "get_next_line.h"

size_t	ft_strlen(const char *s)
{
	size_t	i;

	i = 0;
	while (s[i])
		i++;
	return (i);
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	int		i;
	int		j;
	int		slen;
	char	*res;

	i = 0;
	j = 0;
	slen = ft_strlen(s1) + ft_strlen(s2);
	if (!s1 || !s2)
		return (NULL);
	res = malloc((slen + 1) * sizeof(char));
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

int	ft_check_buff(char* buffer)
{	
	int	i;

	i = 0;
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

	buffer = malloc(BUFFER_SIZE + 1);
	counter = 0;
	while (counter <= BUFFER_SIZE)
	{
		read(fd, &buffer[counter], sizeof(char));
		counter++;
	}
	buffer[counter] = 0;
	counter = 0;
	return (buffer);
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
		while (src[i] != 0 && (i < size - 1))
		{
			dst[i] = src[i];
			i++;
		}
		dst[i] = 0;
	}
	return (j);
}

char	*get_next_line(int fd)
{
	char	*process_buff;
	char	*ret;
	char	*buffer;
	int		line_index;

	buffer = ft_fill_buffer(fd);
	process_buff = ft_strdup(buffer);
	free (buffer);
	line_index = ft_check_buff(process_buff);
	if(line_index == -1)
	{
		ft_fill_buffer(fd);
		ft_strjoin(buffer, process_buff);
	}
	else
	{
		ret = ft_calloc((line_index + 1), sizeof(char)); 
		ft_strlcpy(ret, process_buff, line_index + 1);
		free(process_buff);
		return (ret);
	}

}








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
	int bytes_written = fprintf(fp, "hello\n edee\n");
	fclose(fp);
	int fd = open("hello.txt", O_RDONLY);

	line = get_next_line(fd);
	printf("%s", line);
	//line = get_next_line(fd);
	//printf("%s", line);

}
