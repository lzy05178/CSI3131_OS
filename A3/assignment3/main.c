#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <semaphore.h>
#include <time.h>


int num_students;
sem_t ta_sem;
sem_t chair_sem;
pthread_mutex_t sleep_lock = PTHREAD_MUTEX_INITIALIZER;
int count;


void *student_thread(void *param);
void *ta_thread(void *param);

int main(int argc, char const *argv[])
{   
    srand(time(NULL));
    num_students=5;
    count=num_students;
    sem_init(&ta_sem,0,1);
    sem_init(&chair_sem,0,3);

    pthread_t ta_id;
    pthread_create(&ta_id,NULL, ta_thread,NULL);


    
    
    pthread_t s_ids[num_students];
    for (int i = 0; i <num_students; i++)
    {
        pthread_create(&s_ids[i],NULL, student_thread, &i);
    }
    
    for (int i = 0; i < num_students; i++)
    {
        pthread_join(s_ids[i],NULL);
    }
    
    
    /* code */
    pthread_join(ta_id,NULL);
    
    
    return 0;
}


void *student_thread(void *param){
    int s_id = *(int *)param;
    while (1)
    {
        /* code */
        int num = rand() % 5+3;
        printf("Student-%d is programming for %d seconds\n",s_id,num);
        sleep(num);
        printf("Student-%d needs help.\n",s_id);
        
        int chair_sem_value;
        int ta_sem_value;
        sem_getvalue(&chair_sem, &chair_sem_value);
        sem_getvalue(&ta_sem, &ta_sem_value);
        if (chair_sem_value == 0)
        {
            printf("Student-%d goes back.\n",s_id);
            continue;
        }else if (chair_sem_value<=3 || ta_sem_value==0)
        {
            //get a chair
            sem_wait(&chair_sem);
            printf("Student-%d is waiting on a chair.\n", s_id);
            //blocked until TA is free
            sleep(3);
            sem_wait(&ta_sem);
            sem_post(&chair_sem);
            printf("TA is helping student-%d\n",s_id);
            sleep(num);//瞎改
            printf("TA is done for student-%d\n",s_id);
            sem_post(&ta_sem);
            count--;
            // break;
        }else{
            sem_wait(&ta_sem);
             printf("TA is helping student-%d\n",s_id);
            sleep(5);
            printf("TA is done for student-%d\n",s_id);
            pthread_mutex_unlock(&sleep_lock);
            sem_post(&ta_sem);
            count--;
            // break;
        }
        
        
    }
    pthread_exit(0);
}
    void *ta_thread(void *param){
        while (count>0)
        {
            int ta_sem_value;
            sem_getvalue(&ta_sem, &ta_sem_value);
            if (ta_sem_value==1)
            {
                printf("TA is napping.\n");
                pthread_mutex_lock(&sleep_lock);
            }
    }
    pthread_exit(0);
    
}
