/*==============================================================================\
* Copyright(C)2015 Chudai.
*
* File name    : p173_setjmp_longjmp.c
* Version      : v1.0.0
* Author       : 初代
* Date         : 2015/12/28
* Description  : 测试longjmp对各类变量的影响
* Function list: 1.
*                2.
*                3.
* History      :
\*==============================================================================*/

#include "apue.h"
#include <setjmp.h>

static void     f1(int, int, int, int);
static void     f2(void);

static jmp_buf  jmpbuffer;
static int      globval;

int
main(void)
{
     int                autoval = 0;
     register   int     regival = 0;
     volatile   int     volaval = 0;
     static     int     statval = 0;

     globval = 1;
     autoval = 2;
     regival = 3;
     volaval = 4;
     statval = 5;

     if (setjmp(jmpbuffer) != 0)
     {
          printf("after longjmp:\n");
          printf("globval = %d, autoval = %d, regival = %d, "
                  "volaval = %d, statval = %d.\n",
                  globval, autoval, regival, volaval, statval);
          exit(0);
     }

     globval = 95;
     autoval = 96;
     regival = 97;
     volaval = 98;
     statval = 99;

     f1(autoval, regival, volaval, statval);

     exit(0);
}

static void
f1(int i, int j, int k, int l)
{
     printf("in f1():\n");
     printf("globval = %d; autoval = %d; regival = %d;"
             "volaval = %d; statval = %d.\n",
             globval, i, j, k, l);

     f2();
}

static void
f2(void)
{
     longjmp(jmpbuffer, 1);
}
