#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main() {
    printf("hello (pid:%d)\n", getpid());
    // fork = create a proces that is almost the exact copy of the caller
    // without reprocessing what already process, i.e. we see the hello printf
    // only once
    const int rc = fork();
    if (rc < 0) {
        fprintf(stderr, "fork failed\n");
        exit(1);
    }
    if (rc == 0) {
        // we are in the child process
        printf("child (pid:%d)\n", (int) getpid());
    } else {
        // we are in the parent process
        printf("parent of %d (pid:%d)\n", rc, (int) getpid());
    }
    return 0;
}
