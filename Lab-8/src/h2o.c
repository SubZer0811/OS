#include<stdio.h>
#include<pthread.h>
#include<semaphore.h>
#include <unistd.h>

int hydrogen = 0, oxygen = 0, bcount = 0;
sem_t mutex, hydroqueue, oxyqueue, b_mutex, sbarrier;

void barrier_wait(){

    // sem_wait(&b_mutex);
    // bcount++;
    // sem_post(&b_mutex);

    // if(bcount == 3){
    //     sem_post(&sbarrier);
    // }

    // sem_wait(&sbarrier);
    // sem_post(&sbarrier);
}

void bond(){

    static int i = 0;
    i++;

    if(i%3 == 0){
        printf("[+ H2O] Water mol # %d created\n", i/3);
    }
}

void * o_fn(void *arg){

    sem_wait(&mutex);
    oxygen += 1;
    if(hydrogen >= 2){
        sem_post(&hydroqueue);      // 1
        sem_post(&hydroqueue); //increase by 2 so twice --> allows 2 H molecules
        hydrogen -= 2;
        sem_post(&oxyqueue);        // 1
        oxygen -= 1;
    }
    else{
        sem_post(&mutex);
    }
    
    sem_wait(&oxyqueue);
    printf("[+ O] one Oxygen is ready\n");
    bond();
    barrier_wait();
    sem_post(&mutex);
}

void *h_fn(void *arg){

    sem_wait(&mutex);
    hydrogen += 1;

    if(hydrogen >= 2 && oxygen >= 1){
        sem_post(&hydroqueue);
        sem_post(&hydroqueue);
        hydrogen -= 2;
        sem_post(&oxyqueue);
        oxygen -= 1;
    }
    else{
        sem_post(&mutex);
    }

    sem_wait(&hydroqueue);
    printf("[+ H] 1 Hydrogen molecule ready\n");
    bond();

    barrier_wait(); 
}

int main(){

    sem_init(&b_mutex, 0, 1);
    sem_init(&sbarrier, 0, 0);
    sem_init(&mutex, 0, 1);
    sem_init(&oxyqueue, 0, 0);
    sem_init(&hydroqueue, 0, 0);

    pthread_t o_thread[10], h_thread[20];

    for(int i = 0; i<5; i++){
        pthread_create(&o_thread[i], NULL, o_fn, NULL);
        pthread_create(&h_thread[i], NULL, h_fn, NULL);
        pthread_create(&h_thread[i+10], NULL, h_fn, NULL);
    }

    for(int i = 0; i<5; i++){
        pthread_join(o_thread[i], NULL);
        pthread_join(h_thread[i], NULL);
        pthread_join(h_thread[i+10], NULL);
        
    }
    return 0;
}