#include "apue.h"
static void 
sig_hup(int signo)
{
    printf("SIGHUP recived, pid = %ld\n", (long)getpid());
}
