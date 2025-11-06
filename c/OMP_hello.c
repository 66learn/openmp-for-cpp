#define VERSION_2

/*------------------version one-----------------------*/

#ifdef VERSION_1

#include <omp.h>
#include <stdio.h>

int main()
{
    int nthreads, tid;

    #pragma omp parallel private(nthreads,tid)
    {
        tid=omp_get_thread_num(); // 获取线程号
        printf("Hello world from OpenMP thread %d\n", tid);
        if (tid==0)
        {
            nthreads=omp_get_num_threads(); // 获取线程个数
            printf("Number of threads %d\n", nthreads);
        }
    }

    return 0;
}

#endif

/*------------------version one-----------------------*/

/*-----------------------------------------------------
Hello world from OpenMP thread 5
Hello world from OpenMP thread 3
Hello world from OpenMP thread 2
Hello world from OpenMP thread 4
Hello world from OpenMP thread 6
Hello world from OpenMP thread 1
Hello world from OpenMP thread 7
Hello world from OpenMP thread 0
Number of threads 8
-------------------------------------------------------*/

/*------------------version two-----------------------*/

#ifdef VERSION_2

#include <iostream>
#include <omp.h>

using std::cout;
using std::endl;

int main()
{
    #pragma omp parallel 
    {
        int tid = omp_get_thread_num();
        cout << "hello from " << tid << endl;
        if (tid == 0)
        {
            int threads_num = omp_get_num_threads();
            cout << "number of threads is " << threads_num << endl;
        }
    }

    return 0;
}
#endif


/*------------------version two-----------------------*/

/*-----------------------------------------------------
hello from hello from 40hello from 5hello from 
number of threads is 8


6
hello from 7
hello from 1
hello from 3
hello from 2
-------------------------------------------------------*/
