/******************************************************************************
 * Project Name:    NA
 * File Name:       NA
 *
 * Description: Usage of Condition Variables
 *              Target systems:           Ubuntu20
 *              Compiler:                 GCC
 *
 *****************************************************************************/
/******************************************************************************
 *  INCLUDES
 *****************************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <pthread.h>
#include <unistd.h>

/******************************************************************************
 *  DEFINES & MACROS
 *****************************************************************************/
#define MAX_COUNT 10
/******************************************************************************
 *  GLOBAL VARIABLE
 *****************************************************************************/
/**
 * @brief    Declear random-value variable
 */
char random_num;
char buffer = 0;

pthread_mutex_t lock;
pthread_cond_t cond;
char buffer_full = 0;

/******************************************************************************
 *  GLOBAL FUNCTION
 *****************************************************************************/
/**
 *   @brief      This function generate a random value for referenced input
 *
 *   @param[in]  char                   random_num
 *
 *   @return     void                   NA
 *
 *   @note       This function should be called by producer.
 *
 */
void Generate_Random()
{
    static char first_call = 0;

    /* Check first time call this function */
    if (!first_call)
    {
        srand(time(NULL));
        first_call = 1;
    }

    /* Calculate random number */
    random_num = rand() % 10 + 1;
}

/**
 *   @brief      This function check duplicate variable
 *
 *   @param[in]  char                   random_num
 *
 *   @return     char                   TRUE (if the value is duplicated from the last time)
 *                                      FALSE (if the value is different from the last time)
 *
 *   @note       This function should be called by producer.
 *
 */
char Check_Duplicate(char random_num)
{
    static char prev_value = 0;

    /* Check if this function is called first time*/
    if (!prev_value)
    {
        prev_value = random_num;
    }
    /* Check current value and previous value */
    else if (random_num == prev_value)
    {
        return 1; /* FALSE */
    }

    /* Update previous value */
    prev_value = random_num;

    return 0; /* TRUE */
}

/**
 *   @brief      This function will be the Producer
 *
 *   @param[in]  void                   NA
 *
 *   @return     void                   NA
 *
 *   @note       NA
 *
 */
void *Producer(void *arg)
{
    static char count = 0;

    while (count++ < MAX_COUNT)
    {
        /* Lock mutex */
        pthread_mutex_lock(&lock);

        /* Assign random value to global variable */
        do
        {
            Generate_Random();
        } while (Check_Duplicate(random_num));
        printf("[PRODUCER] produce number = %d\n", random_num);
        buffer_full = 1;

        /* Send signal to Consumer */
        pthread_cond_signal(&cond);

        /* Unlock mutex */
        pthread_mutex_unlock(&lock);
        sleep(1);
    }

    /* Clean thread while exiting */
    pthread_exit(NULL);
}

/**
 *   @brief      This function will be the Consumer
 *
 *   @param[in]  void                   NA
 *
 *   @return     void                   NA
 *
 *   @note       NA
 *
 */
void *Consumer(void *arg)
{
    static char count = 0;

    while (count++ < MAX_COUNT)
    {
        /* Lock mutex */
        pthread_mutex_lock(&lock);

        /* Consumer wait for signal from Producer */
        while (!buffer_full)
        {
            pthread_cond_wait(&cond, &lock);
        }
        printf("[CONSUMER] receive number = %d\n", random_num);
        buffer_full = 0;

        /* Unlock mutex */
        pthread_mutex_unlock(&lock);
    }

    /* Clean thread while exiting */
    pthread_exit(NULL);
}

int main()
{
    /* Initialize threads and mutex lock*/
    pthread_t prod, cons;
    pthread_mutex_init(&lock, NULL);
    pthread_cond_init(&cond, NULL);

    /* Create thread*/
    pthread_create(&prod, NULL, &Producer, NULL);
    pthread_create(&cons, NULL, &Consumer, NULL);

    /* Join to prevent zombie thread */
    pthread_join(prod, NULL);
    pthread_join(cons, NULL);
    return 0;
}
