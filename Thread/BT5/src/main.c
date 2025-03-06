#include "thread.h"


int main() {
    /* Run for the first time */
    pthread_rwlock_init(&rwlock, NULL);
    Init_Writer();
    Init_Reader();
    DeInit_Reader();
    DeInit_Writer();
    pthread_rwlock_destroy(&rwlock);

    /* Run for the second time */
    pthread_rwlock_init(&rwlock, NULL);
    Init_Writer();
    Init_Reader();
    DeInit_Reader();
    DeInit_Writer();
    pthread_rwlock_destroy(&rwlock);
    return 0;
}
