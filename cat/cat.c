#include <stdio.h>
#include <fcntl.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/uio.h>
#include <unistd.h>
#include <errno.h>

/*
 * https://linuxize.com/post/linux-cat-command/
 */

int BUFFER_SIZE = 4096;
int main(int argc, char*argv[]){
	int fd=0;
	char buf[BUFFER_SIZE];
	ssize_t leitura=0;
	int i = 1;

	if(argc<2){
		fprintf(stderr, "uso: %s arquivo\n", argv[0]);
		return 1;
	}else{
		// ex. cat arquivo1.txt arquivo2.txt ...
		// le todos os arquivos de entrada, 
		// comeca a partir de 1 pq 0 é o programa
		while(i<argc) {
			fd = open(argv[i], O_RDONLY);
			if(fd<0){
				perror(argv[i]);
				return 1;
			}
			// le o arquivo atual até EOF 
			for (;;){
				leitura=read(fd, buf, sizeof(buf));
				if(leitura==0) break;//EOF
				if(leitura<0){
					if(errno==EINTR) continue;// interrupcao
					perror(argv[i]);
					return 1;
				}
				write(1,buf,leitura);
			}
			close(fd);
			i++;
		}

	}
	
	return 0;
}
