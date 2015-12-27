/*==============================================================================\
* Copyright(C)2015 Chudai.
*
* File name    : p131_print_buf_stat.c
* Version      : v1.0.0
* Author       : 初代
* Date         : 2015/12/27
* Description  : 为3个标准流以及一个普通文件关联的流打印有关缓冲的状态信息
* Function list: 1.
*                2.
*                3.
* History      :
\*==============================================================================*/


#include "apue.h"

void    pr_stdio(const char *, FILE *);
int     is_unbuffered(FILE *);
int     is_linebuffered(FILE *);
int     buffer_size(FILE *);

int
main(void)
{
    FILE    *fp = NULL;

    fputs("enter any character\n", stdout);

    if (getchar() == EOF)
    {
         err_sys("getchar error");
    }
    fputs("one line to standard error\n", stderr);

    pr_stdio("stdin", stdin);
    pr_stdio("stdout", stdout);
    pr_stdio("stderr", stderr);

    if ((fp = fopen("/etc/passwd", "r")) == NULL)
    {
         err_sys("fopen error");
    }

    if (getc(fp) == EOF)
    {
        err_sys("getc error");
    }
    pr_stdio("/etc/passwd", fp);

    exit(0);
}

void
pr_stdio(const char *name, FILE *fp)
{
     printf("stream = %s, ", name);

     if (is_unbuffered(fp))
     {
         printf("is_unbuffered");
     }
     else if (is_linebuffered(fp))
     {
          printf("is_linebuffered");
     }
     else
     {
         printf("fully buffered");
     }

     printf(", buffer size = %d\n", buffer_size(fp));
}


int
is_unbuffered(FILE *fp)
{
     return (fp->_flags & _IO_UNBUFFERED);
}

int is_linebuffered(FILE *fp)
{
    return (fp->_flags & _IO_LINE_BUF);
}

int buffer_size(FILE *fp)
{
     return (fp->_IO_buf_end - fp->_IO_buf_base);
}
