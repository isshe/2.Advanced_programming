/*==============================================================================\
* Copyright(C)2015 Chudai.
*
* File name    : apue.h
* Version      : v1.0.0
* Author       : 初代
* Date         : 2015/08/31
* Description  : unix 环境高级编程的头文件
* Function list: 1.
*                2.
*                3.
* History      :
\*==============================================================================*/

#ifndef _APUE_H
#define _APUE_H

#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>
#include <string.h>
#include <unistd.h>
#include <signal.h>
#include <stdarg.h>         //va_start()等, ISO c variable arguments
#include <errno.h>
#include <error.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/termios.h>    //???

#if defined(MACOS) || !defined(TIOCGWINSZ)
#include <sys/ioctl.h>
#endif


#define MAXLINE             4096        //max line lenght

#define MAX(a, b)           ((a) > (b) ? (a) : (b))     //这里改大写了

#define	FILE_MODE	(S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH)

typedef void Sigfunc(int);      //for signal handlers

void    err_msg(const char *, ...);     //app misc_source
void    err_dump(const char *, ...) __attribute__((noreturn));  //没返回
void    err_quit(const char *, ...) __attribute__((noreturn));
void    err_ret(const char *, ...);
void    err_sys(const char *, ...) __attribute__((noreturn));
void    err_cont(int, const char *, ...);
void    err_exit(int, const char *, ...) __attribute__((noreturn));


#endif

