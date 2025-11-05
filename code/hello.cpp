#include <iostream>
#include <omp.h>
#include <chrono>

#ifdef _WIN32          // If it is a Windows system
#include <windows.h>   // Include Windows Sleep function
#else                  // If it is a Linux/Unix system
#include <unistd.h>    // Include sleep function (in seconds) or usleep function (in microseconds)
#endif

using std::cout;
using std::endl;

int main(int argc, char* argv[])
{
    int threads = 0;
//    double start_time = omp_get_wtime();
    auto start = std::chrono::high_resolution_clock::now();

    #pragma omp parallel private(threads)
    {
        int tid = omp_get_thread_num();
        sleep(1*tid);
        #pragma omp critical
        {
            cout << "hello from thread " << tid << endl;
            for (int i = 0; i < 100000000; i++)
            {
                i++;
                i--;
            }
        }
        #pragma omp barrier
        if(tid == 0)
        {
            threads = omp_get_num_threads();
            cout << "number of threads is " << threads << endl;
            cout << "I am thread " << tid << endl;
        }
    }

//    double end_time = omp_get_wtime();
//    double elapsed_time = end_time - start_time;
    auto end = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);

    cout << "Time elapsed: " << duration.count() << " microseconds" << endl;
//    cout << "total time is " << elapsed_time << endl;
    
    return 0;    

}
