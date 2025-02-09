#include <stdio.h>
#include <sys/stat.h>
#include <sys/file.h>
#include <unistd.h>

int main()
{
    /* Write data lần 1 */
    int fd = open("test.txt", O_RDWR | O_APPEND | O_CREAT, 0666);
    if (fd == -1)
    {
        perror("Error opening file");
        return 1;
    }

    // Di chuyển con trỏ về đầu tệp
    lseek(fd, 0, SEEK_SET);

    // Ghi dữ liệu
    write(fd, "1st write", sizeof("1st write"));
    close(fd);

    /* Write data lần 2 */
    fd = open("test.txt", O_RDWR | O_APPEND | O_CREAT, 0666);
    if (fd == -1)
    {
        perror("Error opening file");
        return 1;
    }

    // Di chuyển con trỏ về đầu tệp
    lseek(fd, 0, SEEK_SET);

    // Ghi dữ liệu
    write(fd, "2nd write", sizeof("2nd write"));
    close(fd);
    return 0;
}