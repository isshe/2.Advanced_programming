/*=========================================================================\
* Copyright(C)2016 Chudai.
*
* File name    : p360_getenv_reentrance2.c
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
#include <limits.h>
#include <string.h>
#include <pthread.h>
#include <stdlib.h>

#define MAXSTRINGSZ     4096

static pthread_key_t    key;
static pthread_once_t   init_done = PTHREAD_ONCE_INIT;

pthread_mutex_t         env_mutex = PTHREAD_MUTEX_INITIALIZER;

extern char             **environ;

static void thread_init(void)
{
     pthread_key_create(&key, free);
}

char *
getenv(const char *name)
{
    int         i = 0;
    int         len = 0;
    char        *envbuf = NULL;

    pthread_once(&init_done, thread_init);
    pthread_mutex_lock(&env_mutex);

    envbuf = (char *)pthread_getspecific(key);
    if (envbuf == NULL)
    {
         envbuf = (char *)malloc(MAXSTRINGSZ);
         if (envbuf == NULL)
         {
             pthread_mutex_unlock(&env_mutex);
             return NULL;
         }
         pthread_setspecific(key, envbuf);  //关联
    }

    //上面的操作已经获取了空间
    len = strlen(name);
    for (i = 0; environ[i] != NULL; i++)
    {
         if ((strncmp(name, environ[i], len) == 0)
                 && (environ[i][len] == '='))
         {
             strncpy(envbuf, &environ[i][len + 1], MAXSTRINGSZ - 1);//注意减1
             return envbuf;
         }
    }

    pthread_mutex_unlock(&env_mutex);
    return NULL;
}
