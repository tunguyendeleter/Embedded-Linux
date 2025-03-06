#include "thread.h"

Thread_Type Reader[MAX_READER];
Thread_Type Writer[MAX_WRITER];
pthread_rwlock_t rwlock;
int shared_data;

void *Read_Handler(void *arg)
{
    int id = *(int *)arg;
    pthread_rwlock_rdlock(&rwlock);
    printf("[READER %d] Read shared_data = %d\n", id, shared_data);
    pthread_rwlock_unlock(&rwlock);
    return NULL;
}

void *Write_Handler(void *arg)
{
    int id = *(int *)arg;
    pthread_rwlock_wrlock(&rwlock);
    shared_data++;
    printf("[WRITER %d] Increase shared_data\n", id);
    pthread_rwlock_unlock(&rwlock);
    return NULL;
}

void Init_Reader(void)
{
    for (int threadID = 0; threadID < MAX_READER; threadID++)
    {
        Thread_Type *locReader = &Reader[threadID];
        locReader->ThreadID = threadID;
        if (pthread_create(&locReader->Thread, NULL, Read_Handler, &locReader->ThreadID))
        {
            printf("pthread_create() fail\n");
            return;
        }
    }
}

void Init_Writer(void)
{
    for (int threadID = 0; threadID < MAX_WRITER; threadID++)
    {
        Thread_Type *locWriter = &Writer[threadID];
        locWriter->ThreadID = threadID;
        if (pthread_create(&locWriter->Thread, NULL, Write_Handler, &locWriter->ThreadID))
        {
            printf("pthread_create() fail\n");
            return;
        }
    }
}

void DeInit_Reader(void)
{
    for (int threadID = 0; threadID < MAX_READER; threadID++)
    {
        pthread_join(Reader[threadID].Thread, NULL);
    }
}

void DeInit_Writer(void)
{
    for (int threadID = 0; threadID < MAX_WRITER; threadID++)
    {
        pthread_join(Writer[threadID].Thread, NULL);
    }
}