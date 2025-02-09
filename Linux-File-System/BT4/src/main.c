#include <stdio.h>
#include <sys/stat.h>
#include <sys/file.h>
#include <unistd.h>
#include <time.h>

int main(int argc, char **argv)
{
    struct stat sb;
    char filename[20];

    /* Check number of arguments */
    if (argc != 2)
    {
        printf("\n[ERROR] Invalid number of arguments");
        return 0;
    }

    /* Check file is readable */
    sprintf(filename, "./%s", argv[1]);
    if (lstat(filename, &sb) == -1)
    {
        printf("\n[ERROR] Fail to read stat from file %s", filename);
        return 0;
    }
    else
    {
        printf("\n[INFO] Reading stat info from file %s", filename);
    }

    /* Log information from stat */
    printf("\n[INFO] File type: ");
    switch (sb.st_mode & S_IFMT) {
        case S_IFBLK:  printf("block device");            break;
        case S_IFCHR:  printf("character device");        break;
        case S_IFDIR:  printf("directory");               break;
        case S_IFIFO:  printf("FIFO/pipe");               break;
        case S_IFLNK:  printf("symlink");                 break;
        case S_IFREG:  printf("regular file");            break;
        case S_IFSOCK: printf("socket");                  break;
        default:       printf("unknown?");                break;
    }

    printf("\n[INFO] File name: %s\n", filename);
    printf("[INFO] File size: %ld bytes\n", sb.st_size);
    printf("[INFO] Last status change:      %s", ctime(&sb.st_ctime));
    printf("[INFO] Last file access:        %s", ctime(&sb.st_atime));
    printf("[INFO] Last file modification:  %s", ctime(&sb.st_mtime));
    return 0;
}