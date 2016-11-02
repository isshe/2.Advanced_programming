/*=========================================================================\
* Copyright(C)2016 Chudai.
*
* File name    : p357_getenv_reentrance.c
* Version      : v1.0.0
* Author       : 初代
* Date         : 2016/10/31
* Description  :
* Function list: 1.
*                2.
*                3.
* History      :
\*=========================================================================*/

/*-----------------------------------------------------------*
 * 头文件                                                    *
 *-----------------------------------------------------------*/
#include <string.h>
#include <errno.h>
#include <pthread.h>
#include <stdlib.h>

extern char             **environ;
pthread_mutex_t         env_mutex;
static pthread_once_t   init_done = PTHREAD_ONCE_INIT;  //???

static void
thread_init(void)
{
     pthread_mutexattr_t    mutexattr;

     pthread_mutexattr_init(&mutexattr);
     //设置递归属性
     pthread_mutexattr_settype(&mutexattr, PTHREAD_MUTEX_RECURSIVE);
     pthread_mutex_init(&env_mutex, &mutexattr);    //初始化互斥量

     pthread_mutexattr_destroy(&mutexattr);
}

int
getenv_r(const char *name, char *buf, int buflen)
{
     int        i = 0;
     int        len = 0;
     int        olen = 0;

     //只初始化一次
     pthread_once(&init_done, thread_init);

     len = strlen(name);

     pthread_mutex_lock(&env_mutex);

     for (i = 0; environ[i] != NULL; i++)
     {
          if ((strncmp(name, environ[i], len) == 0)
                  && (environ[i][len] == '='))
          {
              olen = strlen(&environ[i][len + 1]);  //获取变量内容长度
              if (olen >= buflen)
              {
                  pthread_mutex_unlock(&env_mutex);
                  return (ENOSPC);      //???
              }

              strcpy(buf, &environ[i][len + 1]);
              pthread_mutex_unlock(&env_mutex);
              return 0;
          }
     }

     pthread_mutex_unlock(&env_mutex);
     return (ENOSPC);
}
