#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>

int main(int argc, char *argv[]) {
    printf("hello (pid:%d)\n", (int) getpid());
    int rc = fork();
    if (rc < 0) {
        fprintf(stderr, "fork failed\n");
        exit(1);
    }

    if (rc == 0) {
        // child (new process)
        printf("child (pid:%d)\n", (int) getpid());
        char *myargs[3];
        // (string duplicate) allocates memory and copies a string into it.
        // It's equivalent to calling malloc() followed by strcpy().
        myargs[0] = strdup("wc");
        // program: "wc"
        // wc prints  the number of lines, words, and bytes
        myargs[1] = strdup("calling_fork.c"); // arg: input file
        myargs[2] = NULL; // mark end of array
        /* • exec — replace the process
        • x — executable
        • v — vector (takes an array of arguments)
        • p — searches the PATH environment variable to find the program
        */
        execvp(myargs[0], myargs); // runs word count
        printf("this shouldn’t print out");
    } else {
        // parent goes down this path
        int rc_wait = wait(NULL);
        printf("parent of %d (rc_wait:%d) (pid:%d)\n", rc, rc_wait, (int) getpid());
    }
    return 0;
}
