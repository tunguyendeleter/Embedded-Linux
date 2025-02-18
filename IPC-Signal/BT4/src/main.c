#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>

/* Hàm xử lý tín hiệu SIGTSTP */
void SIGTSTP_handler(int signum)
{
    printf("\n[INFO] SIGTSTP ignored. Press Ctrl+C to exit.\n");
}

int main()
{
    /* Đăng ký bộ xử lý tín hiệu SIGTSTP */
    if (signal(SIGTSTP, SIGTSTP_handler) == SIG_ERR)
    {
        perror("[ERROR] Failed to catch SIGTSTP");
        exit(EXIT_FAILURE);
    }

    printf("[INFO] Running... Press Ctrl+Z (SIGTSTP) to test. Press Ctrl+C to exit.\n");

    /* Vòng lặp vô hạn để chương trình tiếp tục chạy */
    while (1)
    {
    }

    return 0;
}
