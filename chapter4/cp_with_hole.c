#include <unistd.h>
#include <getopt.h>
#include <string.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>

#define MAX_READ_NUM 1024

int main(int argc, char *argv[])
{
	int srcfile_fd, dstfile_fd;
	int numread, numwrite;
	char tmpbuf[MAX_READ_NUM + 1];
	int i,j;
	int valid_data_size;
	int hole_size;
	
	srcfile_fd = open(argv[1], O_RDONLY);
	if(srcfile_fd == -1)
	{
		fprintf(stderr,"opening src file %s failed: %s\n", argv[1], strerror(errno));
		exit(EXIT_FAILURE);
	}
	
	dstfile_fd = open(argv[2], O_WRONLY | O_CREAT | O_TRUNC, S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP | S_IROTH | S_IWOTH); /* rw-rw-rw */
	if(dstfile_fd == -1)
	{
		fprintf(stderr,"opening dst file %s failed: %s\n", argv[2], strerror(errno));
		exit(EXIT_FAILURE);
	}
	
	while( (numread = read(srcfile_fd, tmpbuf, MAX_READ_NUM)) > 0)
	{
		while(i < numread)
		{
			for(j = i; j < numread; j++)
			{
				if(tmpbuf[j] == '\0')
				{
					break;
				}
			}

			valid_data_size = j-i;
			if( valid_data_size > 0 )
			{
				if( write(dstfile_fd, &tmpbuf[i], valid_data_size) != valid_data_size )
			    {
			        fprintf(stderr,"write to dst file %s failed: %s\n", argv[2], strerror(errno));
			        exit(EXIT_FAILURE);
			    }
			}
			
			for(i=j; i < numread; i++) /* count the number of consecutive '\0'.*/
			{
				if(tmpbuf[i] != '\0')
				{
					break;
				}
			}

			hole_size = i-j;
			if(hole_size > 0)
			{
				/* now we have hole_size bytes hole '0\', make a hole! */
				if( lseek(dstfile_fd, hole_size, SEEK_CUR) == -1 )
		        {
			        fprintf(stderr,"lseek dst file %s failed: %s\n", argv[2], strerror(errno));
			        exit(EXIT_FAILURE);
		        }
			}
		}
	}
	
	if(numread == -1)
	{
		fprintf(stderr,"read from src file %s failed: %s\n", argv[1], strerror(errno));
		exit(EXIT_FAILURE);
	}
	
	if( close(srcfile_fd) == -1)
	{
		fprintf(stderr,"close failed: %s\n", strerror(errno));
		exit(EXIT_FAILURE);
	}
	if( close(dstfile_fd) == -1)
	{
		fprintf(stderr,"close failed: %s\n", strerror(errno));
		exit(EXIT_FAILURE);
	}
	
	exit(EXIT_SUCCESS);
}