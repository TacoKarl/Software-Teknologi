#ifndef VECTOR_HPP_

#define VECTOR_HPP_

//=======================================================

// Class: Vector

// contains a size_-size vector of integers.

// Use the function setAndTest to set all elements

// of the vector to a certain value and then test that

// the value is indeed correctly set

//=======================================================

#include <pthread.h>
static pthread_mutex_t mtx = PTHREAD_MUTEX_INITIALIZER;

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


class Vector
{
public:
   Vector(unsigned int size = 10000) : size_(size)
      {
         pthread_mutex_init(&mtx, nullptr);
        vector_ = new int[size_];
        set(0);
      }
      
   ~Vector()
      {
         pthread_mutex_destroy(&mtx);
        delete[] vector_;
      }

   bool setAndTest(int n)
      {
        set(n);
        return test(n);
      }

private:
   void set(int n)
    {
        for(unsigned int i=0; i<size_; i++) vector_[i] = n;
    }

   bool test(int n)
    {
        for(unsigned int i=0; i<size_; i++) if(vector_[i] != n) return false;
        return true;
    }
   int* vector_;
   unsigned int size_;

};

#endif
