#include <unistd.h>
#include <getopt.h>
#include <string.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>

#define MAX_DATA_NUM 10
int main(int argc, char * argv[])
{
	int file1_fd, file2_fd; 
	char data_buffer[MAX_DATA_NUM] = "doradog";

	file1_fd = open("file_1", O_RDWR | O_TRUNC | O_CREAT, S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP | S_IROTH | S_IWOTH); /* rw-rw-rw */
	if(file2_fd == -1)
	{
		fprintf(stderr,"opening file %s failed: %s\n", argv[1], strerror(errno));
		exit(EXIT_FAILURE);
	}
	if( lseek(file1_fd, 10, SEEK_CUR) == -1 )
	{
	    fprintf(stderr,"lseek dst file %s failed: %s\n", argv[2], strerror(errno));
	    exit(EXIT_FAILURE);
	}
	if(write(file1_fd, data_buffer, MAX_DATA_NUM) == -1)
	{
		fprintf(stderr,"write to STDOUT failed: %s\n", strerror(errno));
		exit(EXIT_FAILURE);
	}
	
	file2_fd = open("file_2", O_RDWR | O_TRUNC | O_CREAT, S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP | S_IROTH | S_IWOTH); /* rw-rw-rw */
	if(file2_fd == -1)
	{
		fprintf(stderr,"opening file %s failed: %s\n", argv[1], strerror(errno));
		exit(EXIT_FAILURE);
	}
	if(write(file2_fd, data_buffer, MAX_DATA_NUM) == -1)
	{
		fprintf(stderr,"write to STDOUT failed: %s\n", strerror(errno));
		exit(EXIT_FAILURE);
	}
	if( lseek(file2_fd, 10, SEEK_CUR) == -1 )
	{
	    fprintf(stderr,"lseek dst file %s failed: %s\n", argv[2], strerror(errno));
	    exit(EXIT_FAILURE);
	}
	if(write(file2_fd, data_buffer, MAX_DATA_NUM) == -1)
	{
		fprintf(stderr,"write to STDOUT failed: %s\n", strerror(errno));
		exit(EXIT_FAILURE);
	}
	if( lseek(file2_fd, 10, SEEK_CUR) == -1 )
	{
	    fprintf(stderr,"lseek dst file %s failed: %s\n", argv[2], strerror(errno));
	    exit(EXIT_FAILURE);
	}
	if(write(file2_fd, data_buffer, MAX_DATA_NUM) == -1)
	{
		fprintf(stderr,"write to STDOUT failed: %s\n", strerror(errno));
		exit(EXIT_FAILURE);
	}

    if( close(file1_fd) == -1)
	{
		fprintf(stderr,"close failed: %s\n", strerror(errno));
		exit(EXIT_FAILURE);
	}
	if( close(file2_fd) == -1)
	{
		fprintf(stderr,"close failed: %s\n", strerror(errno));
		exit(EXIT_FAILURE);
	}
	
	exit(EXIT_SUCCESS);
}