#include <unistd.h>
#include <getopt.h>
#include <string.h>
#include <sys/stat.h>
#include <fcntl.h>
#include "tlpi_hdr.h"

#define MAX_DATA_NUM 50
int main(int argc, char * argv[])
{
	bool file_exist_flag;
	int opt;
	int file_fd  
	char data_buffer[MAX_READ + 1];
	ssize_t read_ret;
	char *string = "a"; /* check -a */
	
	while((opt = getopt(argc, argv, string)) != -1)
	{
		if(opt == 'a')
		{
			file_exist_flag = 1;
		}
		else
		{
			file_exist_flag = 0;
			printf("can't find -a in argv\n");
		}
	}
	
	if(file_exist_flag)
	{
		file_fd = open(argv[2], O_RDWR, S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP | S_IROTH | S_IWOTH); /* rw-rw-rw */
		if(file_fd == -1)
	    {
			errExit("opening file %s", argv[2]);
		}
		if(lseek(file_fd, 0, SEEK_END) == -1) /* Next byte after the end of file */
		{
			errExit("lseek");
		}
	}
	else if(file_exist_flag == 0)
	{
		file_fd = open(argv[1], O_RDWR | O_TRUNC | O_CREATE, S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP | S_IROTH | S_IWOTH); /* rw-rw-rw */
		if(file_fd == -1)
	    {
			errExit("opening file %s", argv[2]);
		}
	}

    while( (read_ret = read(STDIN_FILENO, data_buffer, MAX_DATA_NUM))>0 )
	{
		if(write(STDOUT_FILENO, data_buffer, MAX_DATA_NUM) == -1)
		{
			errExit("write");
		}
		if(write(file_fd, data_buffer, MAX_DATA_NUM) == -1)
		{
			errExit("write");
		}
	}
	
	if(read_ret == -1)
	{
		errExit("read");
	}
	else if(read_ret == 0)
	{
		printf("tee command success\n");
	}

	if( close(read_ret) == -1)
	{
		errExit("close");
	}
	
	exit(EXIT_SUCCESS);
}