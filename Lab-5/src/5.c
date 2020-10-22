#include<stdio.h>
#include<sys/wait.h>
#include<unistd.h>
#include<stdlib.h>
#include<math.h>
#include<sys/ipc.h>
#include<sys/shm.h>

int main(int argc, char const *argv[]){

	int n=atoi(argv[1]);

	int i=0, num=0, sum=0, pow_to=0, j=0;
	struct armstrong {
		int numbers[100];
		int n;
	};

	key_t key = ftok("shmfile", 65);
	int shmid = shmget(key, 5*sizeof(struct armstrong), 0666|IPC_CREAT);
	struct armstrong *armstg = shmat(shmid, 0, 0);

	for(i=0; i<n; i=i+1){

		sum = 0;
		num = i;
		pow_to = 0;
		for(; num>0; num/=10)
			pow_to+=1;
		num = i;

		pid_t pid = fork();
		if(pid == 0){
			while (num>0){
				int digit = num%10;
				sum = sum + pow(digit, pow_to);
				num = num/10;
			}
			if(sum == i){
				armstg->numbers[armstg->n] = i;
				armstg->n += 1;
			}
			exit(0);
		}
		
	}

	wait(NULL);

	printf("Armstrong numbers:\n");
	for(int i=0; i<armstg->n; i++)
		printf("%d\n", armstg->numbers[i]);

	shmdt(armstg);
	shmctl(shmid,IPC_RMID,NULL); 

	return 0;
}