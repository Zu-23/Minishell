#include<stdio.h>
#include<stdlib.h>
//#include"shell_header.h"

typedef enum types
{
	WORD = -1,
	NULL_TERM = '\0',
	PIPE = '|',
	W_SPACE = ' ',
	ENV = '$',
	REDIR_OUT = 1,
	REDIR_IN = 2,
	HERE_DOC = 3,
	REDIR_DOC = 4,
	COMMAND = 5,
}t_types;

int main()
{
  int i = 0;
  t_types tp;

  tp = REDIR_OUT;
  tp++;
  if (tp == 1 || tp == REDIR_IN)
    printf("ok");
}