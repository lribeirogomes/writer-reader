/*************************************************************/
/* Name        : leitor.c                                    */
/*                                                           */
/* Group: 67	Class: 4ª feira - 11h                        */
/*                                                           */
/* Authors     : 72904 - Luís Filipe Pookatham Ribeiro Gomes */
/*               75657 - Paulo Jorge Louseiro Gouveia        */
/*               75694 - Daniel Machado de Castro Figueira   */
/*************************************************************/

#ifndef __DEF_H__
#define __DEF_H__

/*Libraries*/
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <sys/time.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <sys/file.h>
#include <fcntl.h>
#include <errno.h>
#include <pthread.h>
	
/*Built-in Strings*/
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
