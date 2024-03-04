#include <pthread.h>
#include <stdio.h>
#include <unistd.h>

static int count = 0;
struct Data
{
    int loop;
    int id;
} d1, d2;


static void *threadFunc(void* data){
    struct Data * d = (struct Data*)data;
    int loc;
    for (int j = 0; j < d->loop; j++){
        loc = count;
        printf("#%i Hello from thread %i\n", count, d->id);
        loc++;
        count = loc;
        sleep(1);
    }
    return NULL;
}


int main (int argc, int *argv[]){

    pthread_t t1, t2; // thread ID variable
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

    return 0;
}


