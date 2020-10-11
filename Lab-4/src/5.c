#include<stdio.h>
#include<sys/wait.h>
#include<sys/ipc.h>
#include<sys/shm.h>
#include<unistd.h>
#include<stdlib.h>
#include<string.h>

int main (){

	struct histo{
		char chars[95];
		int len;
	};

	char *text = "hi there! how are you?";

	char cur_char = text[0];
	int lens = 1, count = 1;

	key_t key = ftok("shmfile", 65);
	int shmid = shmget(key,sizeof(struct histo),0666|IPC_CREAT);
	struct histo *hist = shmat(shmid, 0, 0);
	
	printf("String: %s\n", text);
	printf("--------Histogram--------\n");

	hist->len = 1;
	hist->chars[hist->len-1] = cur_char;
	
	for(int i=1; i<strlen(text); i++){
		
		if(text[i] == cur_char){
			count += 1;
		}
		else{
			// check if character exists in the list.
			// if not, then add to it and fork
			// else continue
			// printf("%c: %c\n", cur_char, text[i]);
			int flag = 0;
			for(int j=0; j<hist->len; j++){
				if(hist->chars[j] == text[i]){
					flag = 1;
					break;
				}
			}
			if(flag == 0){
				hist->chars[hist->len] = text[i];
				hist->len += 1;
				pid_t pid = fork();
				if(pid == 0){
					count = 1;
					cur_char = text[i];
				}
				else{
					continue;
				}
			}
			else{
				continue;
			}
		}
	}	
	
	printf("%c: %d\n", cur_char, count);
	shmdt(hist);
	shmctl(shmid,IPC_RMID,NULL);

	return 0;
}