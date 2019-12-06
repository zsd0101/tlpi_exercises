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
	int tmpbuf_cp_num;
	
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
		tmpbuf_cp_num = 0;
		for(i = 0; i < numread; i++)
		{		
			if('\0' == tmpbuf[i])
			{
				for(j = 0; j < (numread-i); j++) /* count the number of consecutive '\0'.(if the '0\' is not hole, this function could not figure out the difference)*/
				{
					if('\0' != tmpbuf[i + j])
					{
						break;
					}
				}
			}
			
			if( (i-tmpbuf_cp_num) > 0 )
			{
				if(write(dstfile_fd, &tmpbuf[tmpbuf_cp_num], i-tmpbuf_cp_num) != (i-tmpbuf_cp_num))
			    {
			        fprintf(stderr,"write to dst file %s failed: %s\n", argv[2], strerror(errno));
			        exit(EXIT_FAILURE);
			    }
			    tmpbuf_cp_num += i-tmpbuf_cp_num;
			}

            if(j > 0)
			{
				/* now we have j bytes hole '0\', make a hole! */
				if( lseek(dstfile_fd, j, SEEK_CUR) == -1 )
		        {
			        fprintf(stderr,"lseek dst file %s failed: %s\n", argv[2], strerror(errno));
			        exit(EXIT_FAILURE);
		        }
				tmpbuf_cp_num += j;
				
				i += j;
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