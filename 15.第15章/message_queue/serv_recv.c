/*==============================================================================\
* Copyright(C)2015 Chudai.
*
* File name    : serv_recv.c
* Version      : v1.0.0
* Author       : 初代
* Date         : 2015/12/27
* Description  : 消息队列的接收端
* Function list: 1.
*                2.
*                3.
* History      :
\*==============================================================================*/

#include "apue.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>

struct mymesg
{
    long    mtype;          //positive message type
    char    mtext[512];     //message data, of length nbytes
};

int
main(void)
{
    key_t   key = 2222;
    struct  mymesg  my_msg;
    char    recv_buf[512] = {0};
    int     msgid = 0;

    //创建消息队列
    msgid = msgget(key, 0666 | IPC_CREAT);
    if (msgid == -1)
    {
        err_sys("msgget error");
    }
    else
    {
         printf("msgid = %d\n", msgid);
    }

    //读取队列数据
    while (1)
    {
        if (msgrcv(msgid, recv_buf, 512, 0, 0) == -1)
        {
             err_sys("msgrcv error");
        }

        if (memcmp(recv_buf, "q", 1) == 0)
        {
            printf("接收到“q”，退出！\n");
            break;
        }

        printf("recv msg = %s\n", recv_buf);
    }

    //撤销队列
    if (msgctl(msgid, IPC_RMID, 0) == -1)
    {
         err_sys("msgclt error");
    }


    exit(0);

}
