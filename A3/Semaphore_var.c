//
// Created by Martin Lin on 2023-06-27.
//
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <semaphore.h>
#include <time.h>

//10个thread乱跑,Semaphore控制

int counter;
sem_t sem;


void *thread_increment(void *param);
void *thread_decrement(void *param);

int main(int argc, char *argv[]){
    counter=0;
    sem_init(&sem,0,1);
    pthread_t tids[5];

    for (int i = 0; i < 20; i++) {
        pthread_create(&tids[i],NULL, thread_increment,NULL);
    }

    for (int i = 0; i < 20; i++) {
        pthread_join(tids[i],NULL);
    }

    sem_desstroy(&sem);
    return 0;
}

void *thread_increment(void *param){
    //require lock
    sem_wait(&sem);
    counter++;
    printf("counter-%d\n", counter);
    sem_post(&sem);
    //release lock

}

void *thread_decrement(void *param){
    counter--;
}





//
// Created by Martin Lin on 2023-06-27.
//
