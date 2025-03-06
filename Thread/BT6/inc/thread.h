#ifndef INC_THREAD_H
#define INC_THREAD_H

#include "pthread.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define MAX_COUNTER 4U
#define MAX_SIZE_ARRAY 1000000U

typedef struct Counter
{
    int MaxCount;            /* Max number of elements to count */
    int LocalSum;            /* Sum of all elements */
    short *ArrayPtr;         /* Global array of elements */
    pthread_t CounterThread; /* Counter thread */
} Counter_Type;

extern short MyArray[MAX_SIZE_ARRAY];
extern Counter_Type MyCounter[MAX_COUNTER];
extern long long GlobalSum;
extern pthread_mutex_t lock;

extern void Generate_Random(short *number);
extern void Init_Array(short *Array, int len);
extern void Init_Counter(int CounterIdx);
extern void Print_Array(short *Array, int len);
extern void Count_Array_Without_Thread(short *Array, int len);
extern void DeInit_Counter(int CounterIdx);
extern void *Counter_Handler(void *arg);

#endif /* INC_THREAD_H */