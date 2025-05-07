#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <semaphore.h>
#include <time.h>

//10个thread乱跑,MUTEX控制

int counter;
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;


void *thread_increment(void *param);
void *thread_decrement(void *param);

int main(int argc, char *argv[]){
    counter=0;
    pthread_t tids[5];

    for (int i = 0; i < 20; i++) {
        pthread_create(&tids[i],NULL, thread_increment,NULL);
    }

    for (int i = 0; i < 20; i++) {
        pthread_join(tids[i],NULL);
    }


    return 0;
}

void *thread_increment(void *param){
    //require lock
    pthread_mutex_lock(&mutex);
    counter++;
    printf("counter-%d\n", counter);
    pthread_mutex_unlock(&mutex);
    //release lock

}

void *thread_decrement(void *param){
    counter--;
}





//
// Created by Martin Lin on 2023-06-27.
//
