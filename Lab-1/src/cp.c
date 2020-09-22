/*
This program is for question 1 of the programming assignment.
*/

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<assert.h>

void cp (int argc, char* argv[]){

	if(argc != 3){
		printf("[!] Invalid arguments.\n");
		printf("[!] Correct usage: ./cp <path-to-source-file> <path-to-source-file>\n");
		exit(-1);
	}

	FILE *src, * dest;
	char *sourcefile = argv[1];

	assert(src = fopen(sourcefile, "rb"));

	char *destinationfile = argv[2];
	dest = fopen(destinationfile, "wb");

	int c;
	while((c = fgetc(src)) != EOF){
		fputc(c, dest);
	}
	printf("[+] Successfully copied file\n");
	fclose(src);
	fclose(dest);
}

void rm (int argc, char* argv[]){

	if(argc != 2){
		printf("[!] Invalid arguments.\n");
		printf("[!] Correct usage: ./rm <path-to-source-file>\n");
		exit(-1);
	}

	FILE *src;
	char *sourcefile = argv[1];

	assert(src = fopen(sourcefile, "rb"));
	remove(sourcefile);
	printf("[-] Successfully deleted file\n");

}

int main (int argc, char* argv[]){

	if(strcmp(argv[0], "./cp")==0){
		cp(argc, argv);
	}
	else if(strcmp(argv[0], "./rm")==0){
		rm(argc, argv);
	}

	return 0;
}