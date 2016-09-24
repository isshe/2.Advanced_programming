/*==============================================================================\
* Copyright(C)2015 Chudai.
*
* File name    : client_send.c
* Version      : v1.0.0
* Author       : 初代
* Date         : 2015/12/27
* Description  : 消息队列的发送端
* Function list: 1.
*                2.
*                3.
* History      :
\*==============================================================================*/

#include "apue.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>

struct mymesg
{
    long mtype;
    char mtext[512];
};

int
main(void)
{
     int    msqid = 0;
     key_t  key = 2222;
     char   send_buf[512] = {0};

     //获取队列id
     msqid = msgget(key, 0666);
     if (msqid == -1)
     {
          err_sys("msgget error");
     }
     else
     {
         printf("msqid = %d\n", msqid);
     }


     //发送消息到消息队列, 输入“q”结束
     while(1)
     {
          printf("输入要发送的信息：\n");
          if (fgets(send_buf, 512, stdin) == NULL)
          {
              err_sys("fgets error");
          }

          if (msgsnd(msqid, send_buf, 512, 0) == -1)
          {
               err_sys("msgsnd error");
          }

          if (memcmp(send_buf, "q", 1) == 0)
          {
              break;            //end
          }
     }

     exit(0);
}

