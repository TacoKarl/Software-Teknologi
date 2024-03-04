#include <pthread.h>
#include <stdio.h>

void *hello(void *arg);


int main (int argc, int *argv[]){
    pthread_t t1; // thread ID variable
    int s;
    void *res;

    s = pthread_create(&t1, NULL, hello, "Hello World!\n");
    if (s != 0)
        printf("pthread_create");

    printf("Message from main()\n");
    s = pthread_join(t1, &res);
    if (s!=0)
        printf("pthread_join");


    return 0;
}


void *hello(void *arg){
    char *s = (char*) arg;
    printf("%s", s);
    return NULL;
}