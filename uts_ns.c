#include "ns.h"

int child_main(void* args) {
    char hostname[100];
    printf("child start\n");
    printf("child pid: %d\n", getpid());
    sethostname("child.com", 9);
    gethostname(hostname, 100);
    printf("child hostname: %s\n", hostname);
    printf("child quit\n");
    return 1;
}

int main() {
    char hostname[100];
    printf("parent start\n");
    printf("parent pid: %d\n", getpid());
    gethostname(hostname, 100);
    printf("parent hostname before clone: %s\n", hostname);
    int child_pid = clone(child_main, child_stack + STACK_SIZE,
                          CLONE_NEWUTS | SIGCHLD, NULL);
    printf("child_pid: %d\n", child_pid);
    waitpid(child_pid, NULL, 0);
    gethostname(hostname, 100);
    printf("parent hostname after clone: %s\n", hostname);
    printf("parent quit\n");
    return 0;
}