#include "ns.h"
#include <sys/ipc.h>
#include <sys/msg.h>


#define MSG_KEY 0x12

int child_main(void* args) {
    int msgid = -1;
    printf("child start\n");
    printf("child pid: %d\n", getpid());
    msgid = msgget(MSG_KEY, 0);
    printf("child msgid: %d\n", msgid);
    printf("child quit\n");
    return 1;
}

int main() {
    int msgid = -1;
    printf("parent start\n");
    printf("parent pid: %d\n", getpid());
    msgid = msgget(MSG_KEY, IPC_CREAT);
    printf("parent msgid: %d\n", msgid);
    int child_pid = clone(child_main, child_stack + STACK_SIZE,
                          CLONE_NEWIPC | SIGCHLD, NULL);
    printf("child_pid: %d\n", child_pid);
    waitpid(child_pid, NULL, 0);
    printf("parent quit\n");
    return 0;
}