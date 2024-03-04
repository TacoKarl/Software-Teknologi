#pragma once

#include <pthread.h>

class ScopedLocker{
    private:
    pthread_mutex_t* ownMtx;
    public:
    ScopedLocker(pthread_mutex_t* mtx){
        ownMtx = mtx;
        pthread_mutex_lock(ownMtx);

    }
    ~ScopedLocker(){
        pthread_mutex_unlock(ownMtx);
    }
};