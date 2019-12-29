#include <unistd.h>
#include <getopt.h>
#include <string.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>

int mydup(int oldfd)
{
	int new_fd;
		
    if( -1 == fcntl(oldfd, F_GETFL) )
	{
		//fprintf(stderr,"the file descriptor %d err: %s\n", argv[1], strerror(errno));
		errno = EBADF;
		return -1;
	}
	
	new_fd = fcntl(oldfd, F_DUPFD, 0);
	
	if(-1 == new_fd)
	{
		//fprintf(stderr,"the file descriptor %d err: %s\n", argv[1], strerror(errno));
		return -1;
	}
	
	//fprintf(stdout, "the new file descriptor is %d\n", new_fd);
	
	return new_fd;
}

int main(int argc, char * argv[])
{
    int file1_fd, new_fd;
	char temp_char[] = {"this is a test file for mydup()"};
	char mydup_file[50];
	
	file1_fd = open("mydup_test_file", O_RDWR | O_TRUNC | O_CREAT, S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP | S_IROTH | S_IWOTH); /* rw-rw-rw */
	if(write(file1_fd, temp_char, sizeof(temp_char)) == -1)
	{
		fprintf(stderr,"write to file failed: %s\n", strerror(errno));
		exit(EXIT_FAILURE);
	}

    new_fd = mydup(file1_fd);
	if( -1 == new_fd )
	{
		fprintf(stderr,"mydup() err: %s\n", strerror(errno));
		exit(EXIT_FAILURE);
	}
	
	if( lseek(new_fd, 0, SEEK_SET) == -1)
	{
		fprintf(stderr,"lseek file failed: %s\n", strerror(errno));
		exit(EXIT_FAILURE);
	}	
	if( read(new_fd, mydup_file, sizeof(temp_char)) != sizeof(temp_char) )
	{
		fprintf(stderr,"read to file failed: %s\n", strerror(errno));
		exit(EXIT_FAILURE);
	}
	
	printf("read from new_fd: %s\n",mydup_file);
	
	exit(EXIT_SUCCESS);

}