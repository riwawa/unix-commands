#include <stdio.h>
#include <sys/types.h>
#include <sys/uio.h>
#include <unistd.h>
#include <fcntl.h>

#define LINE 16

int main(int argc, char **argv) 
{
	int fd = 0, i = 1;
	unsigned char buf[LINE];
	ssize_t r;
	if (argc<2) {
		fprintf(stderr, "uso: %s arquivo\n", argv[0]);
		return 1;
	} else {
		
		while (i<argc) {
			fd = open(argv[i], O_RDONLY);
			if(fd<0){
				perror(argv[i]);
			        return 1;
			}
			// le de 16 em 16 bytes e imprime 
			// o hexadecimal
			while((r = read(fd,buf,LINE))>0) {
				for (ssize_t j = 0; j < r;j++) {
					printf("%02x ", buf[j]);
				}
				printf("\n");
				
			}
			if(r<0) {
				perror(argv[i]);
				close(fd);
				return 1;
			}	
				
			close(fd);
			i++;
		}
	}
	return 0;
} 
