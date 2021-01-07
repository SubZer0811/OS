#include<stdio.h>
#include<sys/wait.h>
#include<pthread.h>
#include<string.h>
#define N 5

void *producer(void *args);
void *consumer(void *args);

struct dict{
	char word[30];
	char meaning_1[30], meaning_2[30];
}buf[N];

int flag[] = {0, 0};
int turn = 0;
char search_word[30];

int in = 0,out = 0,end = 0;
int j = 0;

// acquire lock
void lock(int id){

	// set the flag to let the other thread know that this thread wants to acquire a lock
	flag[id] = 1;
 
	// give the other thread a chance first
	turn = 1-id;
 
	// wait till the other thread finishes
	while (flag[1-id] == 1 && turn == 1-id) ;
}

// release lock
void unlock(int id){

	// set the flag to let the other thread know that this thread does not need the lock anymore
	flag[id] = 0;
}


int main(int argc, char *argv[]){

	pthread_t tid[2];
	strcpy(search_word, argv[1]);
	
	pthread_create(&tid[0],NULL,producer,NULL);
	pthread_create(&tid[1],NULL,consumer,NULL);

	pthread_join(tid[0],NULL);
	pthread_join(tid[1],NULL);

	return 0;
}


void *producer(void *args){

	int i=0;
	FILE *fptr=fopen("dict.txt","r");
	while(1){
		lock(0);
		j=0;
		while(j<5){

			char ch;
			char word[20];
			int k=0;
			
			while((ch=fgetc(fptr))!=','){
				buf[j].word[k++]=ch;
			}

			buf[j].word[k]='\0';
			k=0;
			
			while((ch=fgetc(fptr))!=','){
				buf[j].meaning_1[k++]=ch;
			}
			
			buf[j].meaning_1[k]='\0';
			k=0;
			
			while((ch=fgetc(fptr))!='\n'){
				if(ch==EOF){
					buf[j].meaning_2[k]='\0';
					end=1;
					unlock(0);
					return NULL;
				}
				buf[j].meaning_2[k++]=ch;
			}
			
			buf[j].meaning_2[k]='\0';
			j += 1;
		}
		int k;
		i += 1;
		unlock(0);
	}
	pthread_exit(0);
}

void *consumer(void *args){

	int i=0;

	while(1){
				
		lock(1);
		int k=0;
		while(k<j){
			if(strcmp(buf[k].word,search_word)==0){
				printf("[*] Word found: %s\n", buf[k].word);
				printf("[1]  Meaning 1: %s\n", buf[k].meaning_1);
				printf("[2]  Meaning 2: %s\n", buf[k].meaning_2);
				unlock(1);
				return NULL;
			}
			k += 1;
		}
		
		i += 1;
		if(end==1){
			printf("[!]  Word not found!\n");
			return NULL;
		}
		unlock(1);
		
	}

	pthread_exit(0);
}