/*==============================================================================\
* Copyright(C)2015 Chudai.
*
* File name    : p144_getpwnam.c
* Version      : v1.0.0
* Author       : 初代
* Date         : 2015/12/29
* Description  : getpwnam函数的实现
* Function list: 1.
*                2.
*                3.
* History      :
\*==============================================================================*/


#include <pwd.h>
#include <stddef.h>
#include <string.h>

struct passwd *
getpwnam(const char *name)
{
    struct passwd   *ptr = NULL;

    setpwent();

    while((ptr = getpwent()) != NULL)
    {
         if (strcmp(name, ptr->pw_name) == 0)
         {
             break;
         }
    }

    endpwent();

    return (ptr);
}


