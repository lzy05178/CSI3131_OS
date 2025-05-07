#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <semaphore.h>
#include <stdbool.h>
#include <time.h>

pthread_mutex_t mutex;
sem_t students_sem;
sem_t ta_sem;

int num_students_waiting = 0;
int num_chairs_taken = 0;
int num_chairs = 3;
bool chair_available[3] = { false, false, false };

void *student_thread(void *arg);
void *ta_thread(void *arg);

int main()
{
    srand(time(NULL));
    int num_students = 5;
    pthread_t ta_tid;
    pthread_t student_tids[num_students];
    int student_ids[num_students];
    pthread_mutex_init(&mutex, NULL);
    sem_init(&students_sem, 0, 0);
    sem_init(&ta_sem, 0, 0);
    pthread_create(&ta_tid, NULL, ta_thread, NULL);
    for (int i = 0; i < num_students; i++)
    {
        student_ids[i] = i + 1;
        pthread_create(&student_tids[i], NULL, student_thread, &student_ids[i]);
    }
    pthread_join(ta_tid, NULL);
    for (int i = 0; i < num_students; i++)
    {
        pthread_join(student_tids[i], NULL);
    }
    pthread_mutex_destroy(&mutex);
    sem_destroy(&students_sem);
    sem_destroy(&ta_sem);
    return 0;
}

void *student_thread(void *arg)
{
    int student_id = *(int *)arg;

    while (1)
    {
        int programming_time = rand() % 5 + 3;
        printf("Student %d is programming for %d seconds.\n", student_id, programming_time);
        sleep(programming_time);

        pthread_mutex_lock(&mutex);

        if (num_chairs_taken < num_chairs)
        {
            // Find an available chair
            for (int i = 0; i < num_chairs; i++)
            {
                if (!chair_available[i])
                {
                    chair_available[i] = true;
                    num_chairs_taken++;
                    printf("Student %d is waiting in the hallway.\n", student_id);
                    pthread_mutex_unlock(&mutex);
                    sem_post(&students_sem);
                    sem_wait(&ta_sem); // Wait for the TA to signal that it's ready to help
                    break;
                }
            }
        }
        else
        {
            printf("Student %d will come back later.\n", student_id);
            pthread_mutex_unlock(&mutex);
        }
    }
    pthread_exit(NULL);
}

void *ta_thread(void *arg)
{
    while (1)
    {
        pthread_mutex_lock(&mutex);

        if (num_chairs_taken > 0)
        {
            chair_available[num_chairs_taken - 1] = false;
            num_chairs_taken--;
            pthread_mutex_unlock(&mutex);
            sem_post(&ta_sem); // Signal that the TA is ready to help
            printf("TA is helping a student.\n");
            sleep(rand() % 3 + 1);
        }
        else
        {
            printf("TA is taking a nap.\n");
            pthread_mutex_unlock(&mutex);
            sleep(1);
        }
    }
    pthread_exit(NULL);
}
