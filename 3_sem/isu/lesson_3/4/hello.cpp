#include <pthread.h>
#include <stdio.h>
#include <unistd.h>
#include "vector.hpp"

static int shared = 0;
static int count = 0;

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
        loc = shared;
        c = count;
        c++;
        count = c;
        printf("#%i Incremented shared from %i",count, shared);
        loc++;
        shared = loc;
        printf(" to %i\n", shared);
        sleep(1);
    }
    return NULL;
}

static void *writer(void* data){
    Data * d = (Data*)data;
    int testCount = 0;
    int id = d->id;
    while (testCount <= 10){
        d->v->setAndTest(id);
        printf("Test #%i Bolean value: %s\n", testCount, d->v->setAndTest(id) ? "True" : "False");
        testCount++;
        sleep(1);
    }
    return NULL;
}

static void *reader(void* data){
    struct Data * d = (struct Data*)data;
    int c;
    for (int j = 0; j < d->loop; j++){
        usleep(500000);
        c = count;
        c++;
        count = c;
        printf("#%i Read shared variable to be %i\n",count, shared);
        usleep(500000);
    }
    return NULL;
}


int main (int argc, char *argv[]){

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



    return 0;
}


