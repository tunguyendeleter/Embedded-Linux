#include <stdio.h>
#include <sys/stat.h>
#include <sys/file.h>
#include <unistd.h> /* system call */
#include <string.h> /* strcmp */
#include <stdlib.h> /* atoi */

int main(int argc, char **argv)
{
    int fd;
    char filename[20];
    if (argc > 5)
    {
        printf("\n[ERROR]: Number of arguments invalid");
        return 0;
    }

    /* Log argv info */
    for (int i = 0; i < argc; i++)
    {
        printf("\n[INFO]: argv[%i] = %s", i, argv[i]);
    }

    /* Create file */
    sprintf(filename, "./%s.txt", argv[1]);
    if ((fd = open(filename, O_RDWR | O_CREAT, 0666)) == -1)
    {
        printf("\n[ERROR]: Cannot create %s", filename);
        return 0;
    }
    else
    {
        printf("\n[INFO]: Create file %s", filename);
    }

    /* write data into file */
    if ((strcmp(argv[3], "w") == 0) || (strcmp(argv[3], "W") == 0))
    {
        if (write(fd, argv[4], (unsigned int)atoi(argv[2])) == -1)
        {
            printf("\n[ERROR]: Cannot write file %s", filename);
        }
        else
        {
            printf("\n[INFO]: Write %d bytes into file %s", atoi(argv[2]), filename);
        }
    }
    /* Read data from file */
    else if ((strcmp(argv[3], "r") == 0) || strcmp(argv[3], "R") == 0)
    {
        char ReadBuff[100];
        if (read(fd, ReadBuff, (unsigned int)atoi(argv[2])) == -1)
        {
            printf("\n[ERROR]: Cannot read file %s", filename);
        }
        else
        {
            printf("\n[INFO]: Read %d bytes from file %s:", atoi(argv[2]), filename);
            printf("\n%s", ReadBuff);
        }
    }
    /* Invalid operation to read/write file */
    else
    {
        printf("\n[ERROR]: [r/w] Option is invalid, current input: %s", argv[3]);
    }

    return 0;
}