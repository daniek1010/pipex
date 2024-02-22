#include<unistd.h>
#include<sys/types.h>
#include<string.h>
#include<stdio.h>
#include<fcntl.h>
#include "get_next_line.h"

int main(void)
{
    char buf;
    int pipfd[2];
    pid_t x;

    int fd = open("new", O_RDONLY);
    if (pipe(pipfd) == -1)
    return 0;
   if ((x = fork()) == -1)
   { 
    printf("value of xe %d", x);
   return 1;
   }
   else if (x == 0)
   {
    close(pipfd[0]);
    char *str = get_next_line(fd);
    while(str != NULL)
    {
        write(1, str, strlen(str));
        write(1, "\n", 1);
        str = get_next_line(fd);
    }
    close(pipfd[1]);
   }
   else
   {
    close(pipfd[1]);
    while (read(pipfd[0], &buf, 1) > 0)
    write (1, &buf, 1);
    close(pipfd[0]);
   }
  
}