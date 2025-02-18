Create zombie process
+ zombie process create when process child is end before parent process start
+ in the code, process child is start and running about 2 second, then end but parent process is stuck in while(1). So child process becomes zombie process
+ use: ps aux | grep Z to check zombie process

create orphan process
+ orphan process create when process parent end while process child still running.
+ in theo code, process parent is end after 2s starting but the child process still in while (1). so child process become orphan process
+ use: ps aux | grep orphan to check orphan process