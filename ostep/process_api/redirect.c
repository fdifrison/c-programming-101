#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/wait.h>

int main() {
    int rc = fork();
    if (rc < 0) {
        // fork failed
        fprintf(stderr, "fork failed\n");
        exit(1);
    }
    if (rc == 0) {
        // child: redirect standard output to a file
        close(STDOUT_FILENO);
        open("./redirect.output", O_CREAT | O_WRONLY | O_TRUNC, S_IRWXU);
        // now exec "wc"...
        char *myargs[4];
        myargs[0] = strdup("wc");
        // program: wc
        myargs[1] = strdup("-l");
        myargs[2] = strdup("calling_fork.c");
        myargs[3] = NULL;
        // mark end of array
        execvp(myargs[0], myargs);
        // runs word count
    } else {
        // parent goes down this path (main)
        wait(NULL);
    }
    return 0;
}
