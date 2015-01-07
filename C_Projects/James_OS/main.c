#include "header.h"

void initialize(Node **root)
{
	Node *pMem = NULL;
	pMem = (Node *) malloc (sizeof(Node));

	pMem->fType = 'D';
	strcpy(pMem->name, "/");
	pMem->childPtr = NULL;
	pMem->parentPtr = NULL;
	pMem->siblingPtr = NULL;

	*root = pMem;
}

int findCommand(char *line)
{
	char *temp;

	temp = strtok(line, " ");
	//printf("Stringtok: %s \n", temp);

	if (strcmp(temp,"menu") == 0)
	{
		return 0;
	}
	else if (strcmp(temp,"mkdir") == 0)
	{
		return 1;
	}
	else if (strcmp(temp,"rmdir") == 0)
	{
		return 2;
	}
	else if (strcmp(temp,"cd") == 0)
	{
		return 3;
	}
	else if (strcmp(temp,"ls") == 0)
	{
		return 4;
	}
	else if (strcmp(temp,"creat") == 0)
	{
		return 5;
	}
	else if (strcmp(temp,"rm") == 0)
	{
		return 6;
	}
	else if (strcmp(temp,"pwd") == 0)
	{
		return 7;
	}
	else if (strcmp(temp,"clear") == 0)
	{
		return 8;
	}
	else if (strcmp(temp,"quit") == 0)
	{
		return 9;
	}
	else if (strcmp(temp,"load") == 0)
	{
		return 10;
	}
	else if (strcmp(temp,"save") == 0)
	{
		return 11;
	}
	else
	{
		return 999;
	}
	/*temp = strtok(NULL, "/");
	printf("Stringtok2: %s \n", temp);*/
}

int determineDepth(char *line) //Determines depth of directory
{
	int i = 0, count = 0;

	//printf ("Line inside depth function: %s \n", line);

	while (line[i] != NULL)
	{
		if (line[i] == '/')
		{
			count++;
		}
		i++;
	}
	return count;
}

void getName(char *line, char *dirname, char *location, int depth) //Gets path with root
{
	char *temp;
	int count = 0;

	temp = strtok(line, "/");

	while (count < (depth - 1))
	{
		temp = strtok(NULL, "/");
		count++;
	}
	strcpy(location, temp);
	/*printf("Location Name: %s \n", temp);
	system("pause");*/
	temp = strtok(NULL, "/");
	strcpy(dirname, temp);
	/*printf("Dir Name: %s \n", temp);
	system("pause");*/
}

void getName2(char *line, char *dirname, char *location, int depth) //Gets path without root
{
	char *temp;
	int count = 0;

	temp = strtok(line, " ");

	while (count < (depth))
	{
		temp = strtok(NULL, "/");
		count++;
	}
	strcpy(location, temp);
	/*printf("Location Name: %s \n", temp);
	system("pause");*/
	temp = strtok(NULL, "/");
	strcpy(dirname, temp);
	/*printf("Dir Name: %s \n", temp);
	system("pause");*/
}

void getName3(char *line, char *dirname, char *location, int depth)
{
	char *temp;
	int count = 0;

	temp = strtok(line, " ");
	temp = strtok(NULL, " ");

	strcpy(location, temp);
	strcpy(dirname, temp);
}

void menu()
{
	printf("menu - To see this menu. \nload - to load a file structure from file \nmkdir [path] - to make a directory.\ncd [path] - to jump to a directory. \nls [path] - to see the contents of a directory. \npwd - to show what directory you are in. \nrmdir [path] - removes a directory. \ncreat - creates a file node. \nrm - removes a file node. \nclear - to clear the screen \nquit - save and quit\n\n");
}

void pwd(char *currentPath)
{
	printf ("Current path: %s \n", currentPath);
}

void clear()
{
	system("cls");
}

int main (void)
{	
	int ID = 0;
	Node *root = NULL;				    /* root pointers */
	Node *rootCurrent = NULL;
	char line[128], lineBUFFER1[128];   /* user input line */
	char currentPath[128];

	rootCurrent = (Node *) malloc (sizeof(Node));

	initialize(&root);      /* initialize the / DIR of the tree */
	rootCurrent = root;
	strcpy(currentPath, "/");

	printf("Welcome to James OS! \nYou may now type in a command to start. \n(Type menu to see a full list of commands) \n\n");

	while(1)
	{

		  printf("input a command: ");
		  gets(line);

		  strcpy(lineBUFFER1, line);

		  /*printf ("Line in main: %s \n", line);
		  system("pause"); */
	
		  ID = findCommand(lineBUFFER1);

		  switch(ID)
		  { 
			  case 0 : 
				  
				  menu();     
				  
				  break;
			  case 1 :

				  mkdir(&root, &rootCurrent, line);    
				  
				  break;
			  case 2 : 
				  
				  rmdir(&root, &rootCurrent, line);   
				  
				  break;
			  case 3 : 
				  
				  cd(&root, &rootCurrent, line, currentPath);       
				  
				  break;
			  case 4 : 
				  
				  ls(&root, &rootCurrent, line);
				  
				  break;
			  case 5 : 
				  
				  creat(&root, &rootCurrent, line);
				  
				  break;
			  case 6 : 
				  
				  rm(&root, &rootCurrent, line);
				  
				  break;
			  case 7 :
				  
				  pwd(currentPath);

				  break;
			  case 8 :
				  
				  clear();

				  break;
			  case 9 :

				  save(&root, &rootCurrent);

				  return 0;
			  case 10 :

				  load(&root, &rootCurrent);

				  break;
			  case 11 :

				  save(&root, &rootCurrent);

				  break;
			  default:

				  printf("Invalid command! \n");
		  }
	}
}

