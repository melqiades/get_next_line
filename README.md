<img src="https://github.com/melqiades/get_next_line/assets/142016602/89ce4bc6-b23e-451d-bf4e-d11a21a332b1" width=10%>

# get_next_line

A C function that efficiently reads a single line from a file descriptor.

## Features

* **Buffering mechanism:** Minimizes system calls, optimizing performance.
* **Handles various line lengths:** Reads lines of arbitrary sizes.
* **Multiple file descriptor support:** Can manage reading from multiple open files simultaneously.
* **Error handling:** Accurately returns error conditions.

## Usage

1. **Include the header file:**
  ```c
  #include "get_next_line.h"
  ```
2. **Call the get_next_line function:**
  ```c
  char *line = get_next_line(fd);
  ```
    fd: The file descriptor to read from.
    
    line: A pointer to a buffer where the read line will be stored.

3. **Return values:**
A string containing the next line read from the file.
NULL on either end-of-file (EOF) or error.
0 If EOF is reached and no data was previously read.
Free the memory: Remember to free the line pointer after you're done using it.
Example

  ```c
  #include "get_next_line.h"
  
  int main(void)
  {
      int fd = open("my_file.txt", O_RDONLY);
      char *line;
  
      // Read lines until get_next_line returns NULL (EOF or error)
      while ((line = get_next_line(fd)) != NULL))
      {
          printf("%s", line);
          free(line);
      }
      close(fd); 
      return (0);
  }
```

Static variable: get_next_line uses a static variable to buffer leftover data between calls.
