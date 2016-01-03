#include "apue.h"
static void
sig_hup(int signo)
{
    printf("SIGHUP recived, pid = %ld\n", (long)getpid());
}

static void
pr_ids(char *name)
{
    printf("%s: pid = %ld, ppid = %ld, pgrp = %ld, tpgrp = %ld\n",
            name, (long)getpid(), (long)getppid(),
            (long)getpgrp(), (long)tcgetpgrp(STDIN_FILENO));

    fflush(stdout);
}

int
main(void)
{
     char   c;
     pid_t  pid;

     pr_ids("parent");

     if ((pid = fork()) < 0)
     {
          err_sys("fork error");
     }
     else if (pid > 0)      //parent
     {
          sleep(5);
     }
     else
     {
          pr_ids("child");
          signal(SIGHUP, sig_hup);
          kill(getpid(), SIGTSTP);
          pr_ids("child");

          if (read(STDIN_FILENO, &c, 1) != 1)
          {
               printf("read error %d on controlling TTY\n", errno);
          }
     }
     exit(0);
}
