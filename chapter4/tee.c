#include <unistd.h>
#include <getopt.h>
#include <string.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>

#define MAX_DATA_NUM 50
int main(int argc, char * argv[])
{
	char file_exist_flag;
	int opt;
	int file_fd; 
	char data_buffer[MAX_DATA_NUM + 1];
	ssize_t read_ret;
	char *string = "a"; /* check -a */
	
	while((opt = getopt(argc, argv, string)) != -1)
	{
		if(opt == 'a')
		{
			file_exist_flag = 1;
			fprintf(stderr,"find -a in argv\n");
		}
		else
		{
			file_exist_flag = 0;
			fprintf(stderr,"can't find -a in argv\n");
		}
	}
	
	if(file_exist_flag)
	{
		file_fd = open(argv[2], O_RDWR | O_APPEND, S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP | S_IROTH | S_IWOTH); /* rw-rw-rw */
		if(file_fd == -1)
	    {
			fprintf(stderr,"opening file %s failed: %s\n", argv[2], strerror(errno));
			exit(EXIT_FAILURE);
		}
		/* same as if use O_APPEND in open() */
		//if(lseek(file_fd, 0, SEEK_END) == -1) /* Next byte after the end of file */
		//{
		//	fprintf(stderr,"lseek file %s failed: %s\n", argv[2], strerror(errno));
		//	exit(EXIT_FAILURE);
		//}
	}
	else if(file_exist_flag == 0)
	{
		file_fd = open(argv[1], O_RDWR | O_TRUNC | O_CREAT, S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP | S_IROTH | S_IWOTH); /* rw-rw-rw */
		if(file_fd == -1)
	    {
			fprintf(stderr,"opening file %s failed: %s\n", argv[1], strerror(errno));
			exit(EXIT_FAILURE);
		}
	}

    while( (read_ret = read(STDIN_FILENO, data_buffer, MAX_DATA_NUM))>0 )
	{
		fprintf(stderr,"read success , read_ret is %li\n",read_ret);
		if(write(STDOUT_FILENO, data_buffer, read_ret) == -1)
		{
			fprintf(stderr,"write to STDOUT failed: %s\n", strerror(errno));
			exit(EXIT_FAILURE);
		}
		if(write(file_fd, data_buffer, read_ret) == -1)
		{
			fprintf(stderr,"write to file failed: %s\n", strerror(errno));
			exit(EXIT_FAILURE);
		}
	}
	
	if(read_ret == -1)
	{
		fprintf(stderr,"read from STDIN failed: %s\n", strerror(errno));
		exit(EXIT_FAILURE);
	}
	else if(read_ret == 0)
	{
		fprintf(stderr,"tee command success\n");
	}

	if( close(read_ret) == -1)
	{
		fprintf(stderr,"close failed: %s\n", strerror(errno));
		exit(EXIT_FAILURE);
	}
	
	exit(EXIT_SUCCESS);
}