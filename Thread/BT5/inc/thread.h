#ifndef INC_THREAD_H
#define INC_THREAD_H
#include "pthread.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define MAX_READER 5
#define MAX_WRITER 2

typedef struct Thread
{
    /* thread information*/
    int ThreadID;
    pthread_t Thread;
} Thread_Type;

extern Thread_Type Reader[MAX_READER];
extern Thread_Type Writer[MAX_WRITER];
extern pthread_rwlock_t rwlock;
extern int shared_data;

extern void *Read_Handler(void *arg);
extern void *Write_Handler(void *arg);
extern void Init_Reader(void);
extern void Init_Writer(void);
extern void DeInit_Reader(void);
extern void DeInit_Writer(void);

#endif /* INC_THREAD_H */