#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <semaphore.h>
#include <time.h>

pthread_mutex_t mutex;
sem_t students_sem;
sem_t ta_sem;

int num_students_waiting = 0;
int num_chairs_taken = 0;

void *student_thread(void *arg);
void *ta_thread(void *arg);

int main()
{
    srand(time(NULL));
    int num_students = 6;  
    pthread_t ta_tid;
    pthread_t student_tids[num_students];
    pthread_mutex_init(&mutex, NULL);
    sem_init(&students_sem, 0, 0);
    sem_init(&ta_sem, 0, 0);
    pthread_create(&ta_tid, NULL, ta_thread, NULL);
    int student_ids[num_students];
    for (int i = 0; i < num_students; i++) {
        student_ids[i] = i + 1;
        pthread_create(&student_tids[i], NULL, student_thread, &student_ids[i]);
    }
    pthread_join(ta_tid, NULL);
    for (int i = 0; i < num_students; i++) {
        pthread_join(student_tids[i], NULL);
    }
    return 0;
}

void *student_thread(void *arg)
{
    int student_id = *(int *)arg;
    while (1) {
        int programming_time = rand() % 5 + 3;
        printf("Student %d is programming for %d seconds.\n", student_id, programming_time);
        sleep(programming_time);
        pthread_mutex_lock(&mutex);
        if (num_chairs_taken == 3) {
            // No chairs available, student will come back later
            printf("Student %d will come back later.\n", student_id);
            pthread_mutex_unlock(&mutex);
            continue;
        } else if (num_chairs_taken == 0 && num_students_waiting == 0) {
            // All chairs are available and TA is idle, student can ask TA a question
            num_students_waiting = 1;
            printf("Student %d is asking a question to the TA.\n", student_id);
            sem_post(&ta_sem); 
            pthread_mutex_unlock(&mutex);
        } else {
            // Student finds a chair in the hallway and waits
            num_chairs_taken++;
            printf("Student %d is waiting in the hallway.\n", student_id);
            pthread_mutex_unlock(&mutex);
            sem_wait(&students_sem);
        }
    }
    pthread_exit(NULL);
}

void *ta_thread(void *arg)
{
    while (1) {
        pthread_mutex_lock(&mutex);
        if (num_students_waiting > 0) {
            printf("TA is helping a student.\n");
            sleep(rand() % 3 + 1);  
            sem_post(&students_sem);  // Notify student that TA is done helping
            num_students_waiting = 0;
            num_chairs_taken--;
            printf("TA finished helping a student.\n");
        } else {
            printf("TA is taking a nap.\n");
            pthread_mutex_unlock(&mutex);
            sem_wait(&ta_sem);  // Wait for a student to ask a question
        }
        pthread_mutex_unlock(&mutex);
    }
    pthread_exit(NULL);
}