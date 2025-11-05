#include <omp.h>
#include <stdio.h>
#include <iostream>

int main() {
    const int outer_loops = 7;
    const int inner_loops = 2;
    const int thread_num = 3;
    int thread_outer_count[thread_num] = {0}; // 记录每个线程的外层迭代次数
    int thread_inner_count[thread_num] = {0}; // 记录每个线程的内层迭代次数

    #pragma omp parallel for num_threads(thread_num)
    for (int i = 0; i < outer_loops; i++) {
        int thread_id = omp_get_thread_num();
        #pragma omp critical
        {
        std::cout << "thread" << thread_id << "is  doing " << "job" << i << "!!!" << std::endl;
        }
        thread_outer_count[thread_id]++; // 记录外层迭代

        // 内层循环（串行执行）
        for (int j = 0; j < inner_loops; j++) {
            thread_inner_count[thread_id]++; // 记录内层迭代
        }
    }

    // 打印结果
    printf("线程分配总结：\n");
    for (int t = 0; t < thread_num; t++) {
        printf("线程 %d: 分配了 %d 次外层迭代，执行了 %d 次内层迭代\n", 
               t, thread_outer_count[t], thread_inner_count[t]);
    }

    return 0;
}
