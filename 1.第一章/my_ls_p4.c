/*==============================================================================\
* Copyright(C)2015 Chudai.
*
* File name    : my_list_p4.c
* Version      : v1.0.0
* Author       : 初代
* Date         : 2015/08/31
* Description  : 图1-3: 列出一个目录中的所有文件
* Function list: 1.
*                2.
*                3.
* History      :
\*==============================================================================*/

#include "apue.h"
#include <dirent.h>         //??

int main(int argc, char **argv)
{
    DIR     *dp = NULL;
    struct  dirent      *dirp = NULL;
 //   int     n = 0;

    if (argc != 2)
    {
        err_quit("usage: ls directory_name");
    }

    if ( (dp = opendir(argv[1])) == NULL )
    {
         err_sys("can't open %s", argv[1]);
    }

    while ((dirp = readdir(dp)) != NULL)
    {
        printf("%s\n", dirp->d_name);

/*        n++;
        if (n == 4)
        {
             n = 0;
             printf("\n");
        }
*/
//        n++;
    }

//    printf("\n");
    closedir(dp);
    exit(0);
}
