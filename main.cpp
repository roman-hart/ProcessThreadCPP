#include <time.h>
#include <fstream>
#include <string>
#include <unistd.h>  // getpid, replace with <process.h> for Windows
#include <sys/wait.h>  // wait
#include <thread>
using namespace std; 
#define N 20  // matrix rang
#define S 2  // matrix amount, file for each
#define CYCLES 10  // repeat time_test x times from main 

void multiply(int arr1[][N], int arr2[][N], int arr3[][N]) {
    for(int i = 0; i < N; i++){
        for(int j = 0; j < N; j++){
            arr3[i][j] = 0;
            for(int k = 0; k < N; k++) arr3[i][j] += arr1[i][k] * arr2[k][j];
        }
    }
}

void save(string where, int what[][N], int s) {
    ofstream file;
    file.open(where, ios_base::app);
    file << "M0 @ M" << s << ":" << endl; 
    for(int i = 0; i < N; i++) {
        for(int j = 0; j < N; j++){
            file << what[i][j]<<" ";
        }
        file << endl;
    }
    file << endl;
    file.close();
}

void test_actions(int mi_number) {
    auto sourse = "m" + to_string(mi_number) + ".txt";
    int m0[N][N];
    ifstream file("m0.txt");
    for (int i = 0; i < N; ++i) for (int j = 0; j < N; ++j) file >> m0[i][j];
    int mi[N][N];
    ifstream file2(sourse);
    for (int i = 0; i < N; ++i) for (int j = 0; j < N; ++j) file2 >> mi[i][j];
    int res[N][N];
    multiply(m0, mi, res);
    save("output.txt", res, mi_number);
}

void process_approach() {
    int child_number;
    for (int i = 0; i < S; i++) {
        if (fork() == 0) {
            child_number = S - getpid() % S;
            test_actions(child_number);
            exit(0);
        }
    }
    for(int i = 0; i < S; i++) wait(NULL);
}

void thread_approach() {
    thread threads[S];
    for (int i = 0; i < S; ++i) {
        threads[i] = thread( [=] { test_actions(i+1); } );
    }
    for (int i = 0; i < S; ++i) threads[i].join();
}

double time_test(void (*ptr)()) {
    ofstream file("output.txt");
    clock_t tStart = clock();
    (*ptr)();
    return (double)(clock() - tStart)/CLOCKS_PER_SEC;
}

int main() {
    double time_taken = 0;
    for (int i = 0; i < CYCLES; ++i) time_taken += time_test(&process_approach);
    printf("Time taken: %fs\n", time_taken);
}
