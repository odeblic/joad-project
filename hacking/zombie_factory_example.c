/*------------------------------- join_02.c --------------------------------*
On Linux, compile with:
cc -std=c99 -pthread join_02.c -o join_02

Check your system documentation how to enable C99 and POSIX threads on
other Un*x systems.

Copyright Loic Domaigne.
Licensed under the Apache License, Version 2.0.
*--------------------------------------------------------------------------*/

#include "zombie_factory.h"

#include <errno.h>
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

/***************************************************************************/
/* our macro for errors checking                                           */
/***************************************************************************/
#define COND_CHECK(func, cond, retv, errv) \
if ( (cond) ) \
{ \
   fprintf(stderr, "\n[CHECK FAILED at %s:%d]\n| %s(...)=%d (%s)\n\n",\
              __FILE__,__LINE__,func,retv,strerror(errv)); \
   exit(EXIT_FAILURE); \
}

#define ErrnoCheck(func,cond,retv)  COND_CHECK(func, cond, retv, errno)
#define PthreadCheck(func,rc) COND_CHECK(func,(rc!=0), rc, rc)


/*****************************************************************************/
/* thread- print point coordinate and terminate the process                  */
/*****************************************************************************/

struct point
{
    int x;
    int y;
};

void * thread(void * arg)
{
    sleep(5);
    struct point *p = (struct point*) arg;
    printf("(x,y) = (%d,%d)\n", p->x, p->y);
    //exit(EXIT_SUCCESS);
}

int main(void)
{



    void make_zombie_t(int n)
    {
        pthread_t t[n];

        void * z(void * p)
        {
            for(long i=0; i<2000000000; ++i);
            sleep(5);
            return 0;
        }

        while(n > 0)
        {
            if(pthread_create(&t[--n], 0, z, 0))
            {
                puts("error on thread creation");
            }
            else
            {
                printf("thread #%d created\n", n);
            }
        }

        sleep(15);
    }

    printf("I am process #%d\n", getpid());

    make_zombie_t(5);

    pthread_detach(pthread_self());

    return 0;

    make_zombie(5);

    return 0;

    char buffer[111];
    pthread_t tid;  // thread ID
    int rc;         // return code
    struct point p; // point to pass as argument to the thread

    // create thread and pass the point p as argument
    //
    p.x=0;
    p.y=42;
    rc = pthread_create(&tid, NULL, thread, &p);
    PthreadCheck("pthread_create", rc);

    //pthread_detach(pthread_self());

    sleep(10);

    pthread_exit(NULL);
}
