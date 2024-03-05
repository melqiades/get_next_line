
#define BUFFER_SIZE 10
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>
//#include "get_next_line.h"

char	*get_next_line(int fd)
{
	char	buffer[BUFFER_SIZE];
	char	*line;
	int	counter;
	static int	line_len;

	line = malloc(sizeof(char) * 20000);
	counter = 0;
	line_len = 0;
	buffer[counter - 1] = 0;
	while (buffer[(counter - 1)] != '\n')
	{
		if (counter > BUFFER_SIZE)
		{
			line_len += counter;
			counter = 0;
		}
		read(fd, &buffer[counter], sizeof(char));
		line[counter + line_len] = buffer[counter];
		counter++;
	}
	line_len = counter - 1;
	line[line_len + 1] = 0;
	return (line);
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
	int bytes_written = fprintf(fp, "hello\n edee\n");
	fclose(fp);
	int fd = open("hello.txt", O_RDONLY);

	line = get_next_line(fd);
	printf("%s", line);
	line = get_next_line(fd);
	printf("%s", line);

}
*/