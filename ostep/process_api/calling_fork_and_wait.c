#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main() {
    printf("hello (pid:%d)\n", getpid());
    const int rc = fork();
    if (rc < 0) {
        fprintf(stderr, "fork failed\n");
        exit(1);
    }
    if (rc == 0) {
        // we are in the child process
        printf("child (pid:%d)\n", (int) getpid());
    } else {
        // wait until the child finishes, now the output is deterministic,
        // we are sure that child process will print before the parent
        // without wait, is the CPU scheduler to choose and we have no guarantee
        int rc_wait = wait(NULL);
        // we are in the parent process
        printf("parent of %d (rc_wait:%d) (pid:%d)\n", rc, rc_wait, (int) getpid());
    }
    return 0;
}
