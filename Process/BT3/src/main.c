#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <signal.h>

void signal_handler(int signum)
{
    printf("[CHILD] Received SIGUSR1 signal from [PARENT]! (Signal Number: %d)\n", signum);
    printf("[CHILD] Exiting...\n");
    exit(0);
}

int main()
{
    pid_t pid = fork();

    if (pid < 0)
    {
        perror("Fork failed");
        exit(1);
    }
    else if (pid == 0)
    {
        /* Tiến trình con: Định nghĩa handler cho SIGUSR1 */
        signal(SIGUSR1, signal_handler);
        printf("[CHILD] Waiting for SIGUSR1 signal...\n");

        /* Giữ tiến trình con chạy để đợi tín hiệu */
        while (1);
    }
    else
    {
        /* Tiến trình cha: Chờ 3 giây rồi gửi tín hiệu SIGUSR1 cho con */
        sleep(3);
        printf("[PARENT] Sending SIGUSR1 signal to child (PID: %d)\n", pid);

        /* Nhận exit status để tránh process con thành zombie */
        kill(pid, SIGUSR1);
        wait(NULL);

        /* Chờ tiến trình con kết thúc */
        sleep(2);
        printf("[PARENT] Exiting...\n");
    }

    return 0;
}
