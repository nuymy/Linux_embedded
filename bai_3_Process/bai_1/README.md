In process parent cannot use getpid to get PID child process because child process and parent process live in 2 different memory stack frames. So we should use a variable to save PID
