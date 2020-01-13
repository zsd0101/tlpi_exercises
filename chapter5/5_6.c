#include <unistd.h>
#include <getopt.h>
#include <string.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char * argv[])
{
    int fd1, fd2, fd3;
	char read_file[50];
	
	fd1 = open("5_6_test_file", O_RDWR | O_TRUNC | O_CREAT, S_IRUSR | S_IWUSR);
	if(fd1 == -1)
	{
		fprintf(stderr,"fd1 - open file failed: %s\n", strerror(errno));
		exit(EXIT_FAILURE);
	}
	fd2 = dup(fd1);
	if(fd2 == -1)
	{
		fprintf(stderr,"dup fd2 failed: %s\n", strerror(errno));
		exit(EXIT_FAILURE);
	}
	fd3 = open("5_6_test_file", O_RDWR);
	if(fd3 == -1)
	{
		fprintf(stderr,"fd3 - open file failed: %s\n", strerror(errno));
		exit(EXIT_FAILURE);
	}
	
	if(write(fd1, "Hello,", 6) == -1)
	{
		fprintf(stderr,"write to file failed: %s\n", strerror(errno));
		exit(EXIT_FAILURE);
	}
	printf("\r\ncat1 \r\n");
	system("cat 5_6_test_file");
	
	if(write(fd2, "world", 6) == -1)
	{
		fprintf(stderr,"write to file failed: %s\n", strerror(errno));
		exit(EXIT_FAILURE);
	}
	printf("\r\ncat2 \r\n");
	system("cat 5_6_test_file");
	
	if(-1 == lseek(fd2, 0, SEEK_SET))
	{
		fprintf(stderr,"lseek file failed: %s\n", strerror(errno));
		exit(EXIT_FAILURE);
	}
	
	if(write(fd1, "HELLO,", 6) == -1)
	{
		fprintf(stderr,"write to file failed: %s\n", strerror(errno));
		exit(EXIT_FAILURE);
	}
	printf("\r\ncat3 \r\n");
	system("cat 5_6_test_file");
	
	if(write(fd3, "Gidday,", 6) == -1)
	{
		fprintf(stderr,"write to file failed: %s\n", strerror(errno));
		exit(EXIT_FAILURE);
	}
	printf("\r\ncat4 \r\n");
	system("cat 5_6_test_file");
	
	exit(EXIT_SUCCESS);

}