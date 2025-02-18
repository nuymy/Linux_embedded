
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main (int argc, char const * argv[])
{
    pid_t pid, pid_child;
    int counter =0;


    
    pid = fork();
    printf ("pid %d: %d\n",counter, pid); 
    if (pid >=0)
    {
        if (pid == 0)//child process
        {
            printf("In child process\n");
            printf("PID child in child process is: %d\n", getpid());

        }
        else
        {
            printf("In parent process\n");
            printf(" PID in parent process %d\n",pid);
            while (1);
        }
    }
    else
    {
        printf("fork() unsuccessfully\n");
        return EXIT_FAILURE;
    }
    
    return EXIT_SUCCESS;
}

