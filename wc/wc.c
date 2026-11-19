#include <stdio.h>
#include <ctype.h>
#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>

int main(int argc, char **argv){
	int i = 1;
	char buf[4096];
	int fd;
	int linhas, palavras, bytes, dentro;
	ssize_t n;
	if(argc<2) {
		fprintf(stderr, "uso: %s arg1 [arg2,...]\n", argv[0]);
		return 1;
	}
	while(i < argc){
		linhas = palavras = bytes = 0;
		fd = open(argv[i],O_RDONLY);
		if(fd<0){perror(argv[i]); return 1;}

		while((n=read(fd, buf,sizeof buf))>0){
			bytes+=n;
			for (int j = 0; j<n;j++){
				if(buf[j]=='\n') linhas++;
				if(isspace((unsigned char)buf[j])) dentro = 0;
				else if(!dentro){dentro = 1; palavras++;}
			}
			
		}
		if(n<0){perror("read"); close(fd); return 1;}
		close(fd);

		printf("%d %d %d %s\n", linhas, palavras, bytes, argv[i]);
		i++;
	}

}
