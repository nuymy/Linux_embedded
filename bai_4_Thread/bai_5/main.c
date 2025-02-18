/*--------------------------------user code sequence from reader to writer---------------------------------------*/
// #include <stdio.h>
// #include <stdlib.h>
// #include <pthread.h>
// #include <unistd.h>

// #define NUMBER_READERS 5
// #define NUMBER_WRITERS 2

// pthread_rwlock_t rwlock;
// int data_shared = 0;

// void *reader( void *arg)
// {
//     int id = *(int *)arg;
    
//     pthread_rwlock_rdlock(&rwlock); //lock: all threads are allowed to read but cannot write
//     //read data
//     printf("Reader %d reading data %d\n", id, data_shared);
//     pthread_rwlock_unlock(&rwlock); // unlock

//     return EXIT_SUCCESS;
// }

// void *writer (void *arg)
// {
//     int id = *(int *)arg;

//     pthread_rwlock_wrlock(&rwlock); // lock: only one thread can write at a time
//     data_shared++;
//     printf("Writer %d updated shared data %d\n", id, data_shared);
//     pthread_rwlock_unlock(&rwlock); // unlock

//     return EXIT_SUCCESS;
// }

// int main()
// {

//     pthread_t readers[NUMBER_READERS], writers[NUMBER_WRITERS];
//     int readers_ids[NUMBER_READERS], writers_ids[NUMBER_WRITERS];

//     pthread_rwlock_init(&rwlock, NULL);

//         //create reader thread
//     for (int i = 0; i < NUMBER_READERS; i++)
//     {
//         readers_ids[i] = i+1;
//         pthread_create(&readers[i], NULL, reader, &readers_ids[i]);

//     }

//     //create writer thread
//     for (int i = 0; i < NUMBER_WRITERS; i++)
//     {
//         writers_ids[i] = i+1;
//         pthread_create(&writers[i], NULL, writer, &writers_ids[i]);
//     }

//     // wait for thread finished
//     for (int i = 0; i <NUMBER_READERS; i++)
//     {
//         pthread_join(readers[i], NULL);
//     }
//     for (int i = 0; i <NUMBER_WRITERS; i++)
//     {
//         pthread_join(writers[i], NULL);
//     }
//     pthread_rwlock_destroy(&rwlock);

//     printf("Final shared data: %d\n",data_shared);

//     exit(EXIT_SUCCESS);
// }
/*-------------------------------------------------------------------------------------------*/


/*---------------------------user code for random--------------------------------------------*/
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <time.h>

#define NUMBER_READERS 5
#define NUMBER_WRITERS 2

#define TYPE_READER 0
#define TYPE_WRITER 1

pthread_rwlock_t rwlock;
int data_shared = 0;

void *reader( void *arg)
{
    int id = *(int *)arg;
    
    pthread_rwlock_rdlock(&rwlock); //lock: all threads are allowed to read but cannot write
    //read data
    printf("Reader %d reading data %d\n", id, data_shared);
    pthread_rwlock_unlock(&rwlock); // unlock

    return EXIT_SUCCESS;
}

void *writer (void *arg)
{
    int id = *(int *)arg;

    pthread_rwlock_wrlock(&rwlock); // lock: only one thread can write at a time
    data_shared++;
    printf("Writer %d updated shared data %d\n", id, data_shared);
    pthread_rwlock_unlock(&rwlock); // unlock

    return EXIT_SUCCESS;
}

int main()
{
    pthread_t threads[NUMBER_READERS + NUMBER_WRITERS];
    int ids[NUMBER_READERS + NUMBER_WRITERS];
    int type[NUMBER_READERS + NUMBER_WRITERS];

    pthread_rwlock_init(&rwlock, NULL);
    srand(time(NULL));//create random

    //create reader thread with sequence number 1-5
    for (int i = 0; i < NUMBER_READERS; i++)
    {
        ids[i] = i+1;
        type[i] = TYPE_READER;

    }

    //create writer thread with sequence number 6-7
    for (int i = 0; i < NUMBER_WRITERS; i++)
    {
        ids[NUMBER_READERS + i] = i+1;
        type[NUMBER_READERS + i] = TYPE_WRITER;
    }

    //test
    for (int i = 0; i < NUMBER_READERS + NUMBER_WRITERS; i++)
    {
        printf("ID %d: %d - Type: %d\n",i, ids[i], type[i]);
    }

    //random threads
    for (int i = 0; i < NUMBER_READERS + NUMBER_WRITERS; i++)
    {
        int j = rand() % (NUMBER_READERS + NUMBER_WRITERS); 

        // change ID
        int temp_id = ids[i];
        ids[i] = ids[j];
        ids[j] = temp_id;

        // change loại
        int temp_type = type[i];
        type[i] = type[j];
        type[j] = temp_type;
    }

    for (int i = 0; i < NUMBER_READERS + NUMBER_WRITERS; i++)
    {
        printf("ID %d: %d - Type: %d\n",i, ids[i], type[i]);
    }

    //create thread wịth random number
    for (int i = 0; i < NUMBER_READERS + NUMBER_WRITERS; i++) {
        if (type[i] == 0) {
            pthread_create(&threads[i], NULL, reader, &ids[i]);
        } else {
            pthread_create(&threads[i], NULL, writer, &ids[i]);
        }
    }

    // wait for thread finished
    for (int i = 0; i <(NUMBER_READERS + NUMBER_WRITERS); i++)
    {
        pthread_join(threads[i], NULL);
    }

    pthread_rwlock_destroy(&rwlock);

    printf("Final shared data: %d\n",data_shared);

    exit(EXIT_SUCCESS);
}
