#include <pthread.h>
#include <stdio.h>
#include <unistd.h>

static int shared = 0;
static int count = 0;
struct Data
{
    int loop;
    int id;
} d1, d2;


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
        // sleep(1);
    }
    return NULL;
}

static void *reader(void* data){
    struct Data * d = (struct Data*)data;
    int c;
    for (int j = 0; j < d->loop; j++){
        // usleep(500000);
        c = count;
        c++;
        count = c;
        printf("#%i Read shared variable to be %i\n",count, shared);
        // usleep(500000);
    }
    return NULL;
}


int main (int argc, char *argv[]){

    pthread_t inc, read; // thread ID variable
    int s;
    void *res;

    d1.loop = 10;
    d1.id = 1;
    d2.loop = 10;
    d2.id=2;

    printf("Message from main()\n");

    s = pthread_create(&inc, NULL, increment, &d1);
    if (s != 0)
        printf("pthread_create");


    s = pthread_create(&read, NULL, reader, &d2);
    if (s != 0)
        printf("pthread_create");


    s = pthread_join(inc, NULL);
    if (s != 0)
        printf("pthread_join");

    s = pthread_join(read, NULL);
    if (s != 0)
        printf("pthread_join");

    return 0;
}


