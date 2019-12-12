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
	int file_fd;
	int num_bytes;
	int i;
	char testchar = 'z';

    if(argc == 4)
	{
	    file_fd = open(argv[1], O_WRONLY | O_CREAT, S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP | S_IROTH | S_IWOTH); /* rw-rw-rw */
		if(file_fd == -1)
	    {
		    fprintf(stderr,"opening file %s failed: %s\n", argv[1], strerror(errno));
		    exit(EXIT_FAILURE);
	    }
		
		num_bytes = atoi(argv[2]);
	
	    for(i = 0; i<num_bytes; i++)
	    {
			if( lseek(file_fd, 0, SEEK_END) == -1 )
	        {
	            fprintf(stderr,"lseek to end of file %s failed: %s\n", argv[1], strerror(errno));
	            exit(EXIT_FAILURE);
	        }
			if(write(file_fd, &testchar, 1) != 1)
			{
				fprintf(stderr,"write to file failed: %s\n", strerror(errno));
				exit(EXIT_FAILURE);
			}
	    }
		
		if( close(file_fd) == -1)
	    {
		    fprintf(stderr,"close failed: %s\n", strerror(errno));
		    exit(EXIT_FAILURE);
	    }
	    exit(EXIT_SUCCESS);
	}
	else if(argc == 3)
	{
		file_fd = open(argv[1], O_WRONLY | O_APPEND | O_CREAT, S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP | S_IROTH | S_IWOTH); /* rw-rw-rw */
		if(file_fd == -1)
	    {
		    fprintf(stderr,"opening file %s failed: %s\n", argv[1], strerror(errno));
		    exit(EXIT_FAILURE);
	    }
		
		num_bytes = atoi(argv[2]);
	
	    for(i = 0; i<num_bytes; i++)
	    {
			if(write(file_fd, &testchar, 1) != 1)
			{
				fprintf(stderr,"write to file failed: %s\n", strerror(errno));
				exit(EXIT_FAILURE);
			}
	    }
		
		if( close(file_fd) == -1)
	    {
		    fprintf(stderr,"close failed: %s\n", strerror(errno));
		    exit(EXIT_FAILURE);
	    }
	    exit(EXIT_SUCCESS);
	}
	else
	{
		fprintf(stderr,"filename num-bytes [x]\n");
		exit(EXIT_FAILURE);
	}
}