#include <pthread.h>
#include <stdio.h>
#include <unistd.h>
#include "vector.hpp"
#include <semaphore.h>

static int shared = 0;
static int count = 0;

static sem_t sem;
static pthread_mutex_t mtx = PTHREAD_MUTEX_INITIALIZER;

struct Data
{
    int loop;
    int id;
    Vector* v;
};


static void *increment(void* data){
    struct Data * d = (struct Data*)data;
    int loc, c;
    for (int j = 0; j < d->loop; j++){
        sem_wait(&sem);
        loc = shared;
        c = count;
        c++;
        count = c;
        printf("#%i Incremented shared from %i",count, shared);
        loc++;
        shared = loc;
        printf(" to %i\n", shared);
        // sleep(1);
        sem_post(&sem);
    }
    return NULL;
}

static void *writer(void* data){
    Data * d = (Data*)data;
    int testCount = 0;
    int id = d->id;
    while (testCount <= 10){
        sem_wait(&sem);
        d->v->setAndTest(id);
        printf("Test #%i Bolean value: %s\n", testCount, d->v->setAndTest(id) ? "True" : "False");
        testCount++;
        // sleep(1);
        sem_post(&sem);
    }
    return NULL;
}

static void *reader(void* data){
    struct Data * d = (struct Data*)data;
    int c;
    for (int j = 0; j < d->loop; j++){
        sem_wait(&sem);
        // usleep(500000);
        c = count;
        c++;
        count = c;
        printf("#%i Read shared variable to be %i\n",count, shared);
        // usleep(500000);
        sem_post(&sem);
    }
    return NULL;
}


int main (int argc, char *argv[]){
    if (sem_init(&sem, 0, 1) == -1)
        printf("sem_init");
    int threadcount = 2;
    pthread_t thread[threadcount]; // tht2 ID variable
    int s;
    void *res;
    Vector sharedVec;
    int numVecs = 20;
    Data vectorList[numVecs];

    for (int i = 0; i< numVecs; i++){
        vectorList[i].id = i;
        vectorList[i].v = &sharedVec;
    }


    printf("Message from main()\n");

    for (int i = 0; i < threadcount; i++){
        int threadn = pthread_create(&thread[i], NULL, writer, &vectorList[i]);
    }

    for (int i = 0; i < threadcount; i++){
        pthread_join(thread[i], NULL);
        if (s != 0)
            printf("pthread_join");
    }

    sem_destroy(&sem);

    return 0;
}


