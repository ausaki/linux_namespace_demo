#include "ns.h"

int child_main(void* args) {
    printf("child start\n");
    printf("child pid: %d\n", getpid());
    sleep(10);
    printf("child quit\n");
    return 1;
}

int main() {
    printf("parent start\n");
    printf("parent pid: %d\n", getpid());
    int child_pid = clone(child_main, child_stack + STACK_SIZE,
                          CLONE_NEWPID | SIGCHLD, NULL);
    printf("child_pid: %d\n", child_pid);
    waitpid(child_pid, NULL, 0);
    printf("parent quit\n");
    return 0;
}