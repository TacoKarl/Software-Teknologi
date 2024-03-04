#include <pthread.h>
#include <stdio.h>
#include <unistd.h>
#include <semaphore.h>

static int count = 0;
static sem_t sem;

//global mutex
static pthread_mutex_t mtx = PTHREAD_MUTEX_INITIALIZER;

struct Data
{
    int loop;
    int id;
} d1, d2;


static void *threadFunc(void* data){
    struct Data * d = (struct Data*)data;
    int loc;
    for (int j = 0; j < d->loop; j++){
        if (sem_wait(&sem) == -1)
            printf("sem_wait");
        loc = count;
        printf("#%i Hello from thread %i\n", count, d->id);
        loc++;
        count = loc;

        if (sem_post(&sem) == -1)
            printf("sem_post");
    }
    count = 0;
    return NULL;
}


int main (int argc, char *argv[]){

    pthread_t t1, t2; // thread ID variable

    /* Initialize a thread-shared mutex with the value 1 */
    if (sem_init(&sem, 0, 1) == -1)
        printf("sem_init");

    int s;
    void *res;

    d1.loop = 10;
    d1.id = 1;
    d2.loop = 10;
    d2.id=2;

    printf("Message from main()\n");

    s = pthread_create(&t1, NULL, threadFunc, &d1);
    if (s != 0)
        printf("pthread_create");


    s = pthread_create(&t2, NULL, threadFunc, &d2);
    if (s != 0)
        printf("pthread_create");


    s = pthread_join(t1, NULL);
    if (s != 0)
        printf("pthread_join");

    s = pthread_join(t2, NULL);
    if (s != 0)
        printf("pthread_join");

    sem_destroy(&sem);
    
    return 0;
}


