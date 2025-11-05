/*
#include <iostream>
#include <cstdlib>
#include <omp.h>

#ifdef _WIN32          // If it is a Windows system
#include <windows.h>   // Include Windows Sleep function
#else                  // If it is a Linux/Unix system
#include <unistd.h>    // Include sleep function (in seconds) or usleep function (in microseconds)
#endif

using std::cout;
using std::endl;

int main(int argc, char* argv[])
{
    int thread_count=strtol(argv[1],NULL,10);
    int j=0;
    #pragma omp parallel for num_threads(thread_count) shared(j)
    {
        int my_rank=omp_get_thread_num();
         sleep(1*my_rank);

        for(int i=0;i<10;i++){
            int thread_count=omp_get_num_threads();
            #pragma omp critical
            {
                j=j+1;
                cout << "Hello from thread " << my_rank << " of " << thread_count << " i = " << i << ", j = " << j << endl;
            }
        }
    }

    return 0;
}
*/

/*---------------------------------------------------------
1.线程进入临界区的顺序不确定
2.用 4 threads执行，结果如下：
    Hello from thread 0 of 4 i = 0,j = 1.
    Hello from thread 1 of 4 i = 3,j = 2.
    Hello from thread 1 of 4 i = 4,j = 3.
    Hello from thread 1 of 4 i = 5,j = 4.
    Hello from thread 2 of 4 i = 6,j = 5.
    Hello from thread 2 of 4 i = 7,j = 6.
    Hello from thread 3 of 4 i = 8,j = 7.
    Hello from thread 3 of 4 i = 9,j = 8.
    Hello from thread 0 of 4 i = 1,j = 9.
    Hello from thread 0 of 4 i = 2,j = 10.
----------------------------------------------------------*/

#include <iostream>
#include <omp.h>
#include <cstdlib> // 用于 strtol

#ifdef _WIN32
#include <windows.h>
#define SLEEP(seconds) Sleep((seconds) * 1000)
#else
#include <unistd.h>
#define SLEEP(seconds) sleep(seconds)
#endif

using std::cout;
using std::endl;

int main(int argc, char* argv[])
{
    if (argc < 2) {
        cout << "Usage: " << argv[0] << " <number_of_threads>" << endl;
        return 1;
    }
    
    int thread_count = strtol(argv[1], NULL, 10);
    int j = 0; // 这个变量将用于 reduction

    // 分解 parallel 和 for 指令，并使用 reduction 子句
    #pragma omp parallel num_threads(thread_count) reduction(+:j)
    {
        int my_rank = omp_get_thread_num();
        SLEEP(1); // 所有线程睡眠相同时间，模拟均衡负载

        // 使用 for 指令来并行化循环
        #pragma omp for
        for(int i = 0; i < 100; i++) {
            int actual_thread_count = omp_get_num_threads(); // 避免变量名遮蔽
            #pragma omp critical
            {
                j = j + 1; // 此处的 j 是线程本地副本，临界区保护输出和最终累加
                cout << "Hello from thread " << my_rank << " of " << actual_thread_count << " i = " << i << ", j = " << j << endl;
            }
        } 
    }

    // 并行区域结束后，j 是归约后的最终值
    cout << "Final value of j: " << j << endl;
    
    return 0;
}
