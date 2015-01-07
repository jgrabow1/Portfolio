#ifndef MAIN_HEADER
#define MAIN_HEADER

#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include <string.h>

#define NULL 0

typedef enum boolean
{
	FALSE, TRUE
}Boolean;

typedef struct node
{
	char name[64];
	char fType;		//D or F
	struct node *childPtr;
	struct node *siblingPtr;
	struct node *parentPtr;
}Node;

typedef struct list
{
	char line[128];
	struct list *pNext;
}List;

#endif

