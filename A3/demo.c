#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <semaphore.h>
#include <time.h>



//struct thread_args  //类
//{
//    /* data */
//    char *msg;
//    int i;
//};
//
//
//void *thread(void *param);
//
//int main(int argc, char const *argv[]) //注意constant
//{
//    /* code */
//    pthread_t tid;
//
//    struct thread_args args;
//    args.msg ="hello world";
//    args.i=1;
//
//
//    pthread_create(&tid,NULL,thread,&args);//根据地址生成thread
//    pthread_join(tid,NULL);
//}
//
//
//void *thread(void *param){
//    struct thread_args args = *(struct thread_args *)param;
//    // printf("hello, world\n");
//    printf("%s %d\n",args.msg,args.i);
//}
