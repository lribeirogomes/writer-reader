/*************************************************************/
/* Name        : def.c                              	     */
/*                                                           */
/* Group: 67	Class: 4ª feira - 11h                        */
/*                                                           */
/* Authors     : 72904 - Luís Filipe Pookatham Ribeiro Gomes */
/*               75657 - Paulo Jorge Louseiro Gouveia        */
/*               75694 - Daniel Machado de Castro Figueira   */
/*************************************************************/

#ifndef __DEF_H__
#define __DEF_H__

/* libraries */
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <sys/file.h>
#include <fcntl.h>
#include <errno.h>
#include <pthread.h>
#include <signal.h>
#include <semaphore.h>

/* defines */
#define W_THREADS 10
#define W_LOCK 1
#define W_ERRORS 0
#define R_THREADS 10
#define FB_SIZE 20
#define B_SIZE 120

	
/* built-in Strings */
char *_string[10] =    {"aaaaaaaaa\n",
						"bbbbbbbbb\n",
						"ccccccccc\n",
						"ddddddddd\n",
						"eeeeeeeee\n",
						"fffffffff\n",
						"ggggggggg\n",
						"hhhhhhhhh\n",
						"iiiiiiiii\n",
						"jjjjjjjjj\n"};
						
#endif


/*
SO2014-0.txt SO2014-1.txt SO2014-2.txt SO2014-3.txt SO2014-4.txt 
*/

