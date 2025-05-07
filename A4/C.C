#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/mman.h>
#include <sys/wait.h>
#include <fcntl.h>

int factorial(int n) {
    if (n == 0 || n == 1) {
        return 1;
    } else {
        int fact = 1;
        for (int i = 2; i <= n; i++) {
            fact *= i;
        }
        return fact;
    }
}
int getCatalannum(int n) {
    return factorial(2 * n) / (factorial(n + 1) * factorial(n));
}
int main(int argc, char *argv[]) {
    int n = atoi(argv[1]);
    if (n <= 0) {
        printf("Invalid number of Catalan numbers\n");
        return 1;
    }
    int *memory = mmap(NULL, n * sizeof(int), PROT_READ | PROT_WRITE, MAP_SHARED | MAP_ANONYMOUS, 0, 0);
    if (memory == MAP_FAILED) {
        printf("Failed to create shared memory\n");
        return 1;
    }
    pid_t pid = fork();
    if (pid == 0) {
        // Producer process
        for (int i = 0; i < n; i++) {
            memory[i] = getCatalannum(i);
        }
        exit(0);
    } else if (pid > 0) {
        // Consumer process
        wait(NULL);
        for (int i = 0; i < n; i++) {
            printf("%d ", memory[i]);
        }
        printf("\n");
    } else {
        printf("Fork failed\n");
        munmap(memory, n * sizeof(int));
        return 1;
    }
    munmap(memory, n * sizeof(int));
    return 0;
}
