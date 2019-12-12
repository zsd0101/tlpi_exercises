#include <unistd.h>
#include <getopt.h>
#include <string.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>

#define MAX_DATA_NUM 7
int main(int argc, char * argv[])
{
	int file_fd;
	char data_buffer[MAX_DATA_NUM] = "doradog";

	file_fd = open(argv[1], O_WRONLY | O_APPEND, S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP | S_IROTH | S_IWOTH); /* rw-rw-rw */
	if(file_fd == -1)
	{
		fprintf(stderr,"opening file %s failed: %s\n", argv[1], strerror(errno));
		exit(EXIT_FAILURE);
	}
	if( lseek(file_fd, 0, SEEK_SET) == -1 )
	{
	    fprintf(stderr,"lseek to start of file %s failed: %s\n", argv[1], strerror(errno));
	    exit(EXIT_FAILURE);
	}
	if(write(file_fd, data_buffer, MAX_DATA_NUM) == -1)
	{
		fprintf(stderr,"write to file failed: %s\n", strerror(errno));
		exit(EXIT_FAILURE);
	}
	
    if( close(file_fd) == -1)
	{
		fprintf(stderr,"close failed: %s\n", strerror(errno));
		exit(EXIT_FAILURE);
	}
	
	exit(EXIT_SUCCESS);
}