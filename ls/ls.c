#include <stdio.h>
#include <dirent.h>
#include <errno.h> 
#include <string.h>

int main(int argc, char **argv) {
	const char *path = (argc == 2) ? argv[1] : ".";
	if(argc>2){
		fprintf(stderr, "uso: %s [dir]\n", argv[0]);
	}
	DIR *d = opendir(path);
	struct dirent *r;

	if (d==NULL) {
		fprintf(stderr, "ls: %s: %s\n", path, strerror(errno));
		return 1;
	} else {
		errno=0;
		while ((r=readdir(d)) != NULL) {
			printf(" %s\n", r->d_name);
		}
		if (errno!=0) perror(path);
		closedir(d);
	}
	
	return 0;
}
