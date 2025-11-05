#include <iostream>
#include <omp.h>

using namespace std;

int main() {
    const int N = 10;  // 外层循环次数
    const int M = 2;  // 内层循环次数
    const int K = 2;  // 最内层循环次数
    
    cout << "=== OpenMP嵌套循环线程分配测试 ===" << endl;
    cout << "循环维度: N=" << N << ", M=" << M << ", K=" << K << endl;
    cout << "总迭代次数: " << N * M * K << endl;
    cout << "默认线程数: " << omp_get_max_threads() << endl << endl;
    
    // 测试1: 只并行化外层循环
    cout << "1. 只并行化外层循环 (#pragma omp parallel for):" << endl;
    #pragma omp parallel for
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < M; j++) {
            for (int k = 0; k < K; k++) {
                #pragma omp critical
                {
                    cout << "线程 " << omp_get_thread_num() 
                         << " 执行: i=" << i << ", j=" << j << ", k=" << k << endl;
                }
            }
        }
    }
    
    cout << endl;
    
    // 测试2: 使用collapse合并两层循环
    cout << "2. 使用collapse(2)合并两层循环:" << endl;
    #pragma omp parallel for collapse(2)
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < M; j++) {
            #pragma omp critical
            {
                cout << "线程 " << omp_get_thread_num() 
                     << " 执行: i=" << i << ", j=" << j << endl;
            }
        }
    }
    
    cout << endl;
    
    // 测试3: 使用collapse合并三层循环
    cout << "3. 使用collapse(3)合并三层循环:" << endl;
    #pragma omp parallel for collapse(3)
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < M; j++) {
            for (int k = 0; k < K; k++) {
                #pragma omp critical
                {
                    cout << "线程 " << omp_get_thread_num() 
                         << " 执行: i=" << i << ", j=" << j << ", k=" << k << endl;
                }
            }
        }
    }
    
    cout << endl;
    
    // 测试4: 不同的调度策略对比
    cout << "4. 不同调度策略对比 (静态调度):" << endl;
    #pragma omp parallel for schedule(static)
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < M; j++) {
            #pragma omp critical
            {
                cout << "静态调度 - 线程 " << omp_get_thread_num() 
                     << " 执行: i=" << i << ", j=" << j << endl;
            }
        }
    }
    
    cout << endl;
    
    cout << "5. 不同调度策略对比 (动态调度):" << endl;
    #pragma omp parallel for schedule(dynamic, 2)
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < M; j++) {
            #pragma omp critical
            {
                cout << "动态调度 - 线程 " << omp_get_thread_num() 
                     << " 执行: i=" << i << ", j=" << j << endl;
            }
        }
    }
    
    return 0;
}
