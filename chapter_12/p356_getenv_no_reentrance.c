/*=========================================================================\
* Copyright(C)2016 Chudai.
*
* File name    : p356_getenv_no_reentrance.c
* Version      : v1.0.0
* Author       : 初代
* Date         : 2016/10/31
* Description  : getenv 的非可重入版本。
* Function list: 1.
*                2.
*                3.
* History      :
\*=========================================================================*/

/*-----------------------------------------------------------*
 * 头文件                                                    *
 *-----------------------------------------------------------*/

#include <limits.h>
#include <string.h>

#define MAXSTRINGSZ     4096
static char envbuf[MAXSTRINGSZ];
extern char **environ;      //???

char *
getenv(const char *name)
{
     int    i = 0;
     int    len = 0;

     len = strlen(name);

     for (i = 0; environ[i] != NULL; i++)
     {
          if ((strncmp(name, environ[i], len) == 0)
                  && (environ[i][len] == '='))          //确定环境变量
          {
              //复制对应的环境变量到缓冲区。
              strncpy(envbuf, &environ[i][len+1], MAXSTRINGSZ - 1);
              return (envbuf);
          }
     }

     return NULL;
}
