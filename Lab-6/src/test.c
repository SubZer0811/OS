#include<stdio.h>
#include<string.h>
#include<unistd.h>
#include<sys/types.h>
#include<stdlib.h>
#include<time.h>
#include<sys/wait.h>
#include<pthread.h>
#define SIZE 100
#define MAX_THREADS 4
int num;
void *prime(void *param)
{
    int n=*(long long int*)param;
    int flag=1;
    for(int i=2;i<n/2;i++)
    {
        if(n%i==0)
        {
            flag=0;
            pthread_exit(0);
        }
    }
    if(flag==1)
    {
    printf("%d ",n);
    pthread_exit(0);
    }
    

}
int main()
{
    printf("Enter limit upto which prime numbers are to be generated: ");
    scanf("%d",&num);
    pthread_t tid[num-1];
    for(int i=2;i<num;i++)
    {
            
            pthread_create(&tid[i-2],NULL,prime,&i);
            
    }
    for(int i=2;i<num;i++)
    {
            
            pthread_join(tid[i-2],NULL);
    }
    return 0;
}