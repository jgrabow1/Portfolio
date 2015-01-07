#include "header.h"

void load(Node **root, Node **rootC) //Loads state of file system from text file
{
	Node *rTemp = NULL;
	Node *rTempC = NULL;
	List *pList = NULL;
	List *pTemp = NULL;
	char lineBUFFER[128], lineBUFFER2[128];
	char pathInput[128], commandInput[128], commandInput2[128], line[128], newLine[128];
	char *tempSTR;
	int count = 0;

	FILE * lFile;
	lFile = fopen("save.txt", "r");

	pList = (List *)malloc(sizeof(List));
	rTemp = (Node *)malloc(sizeof(Node));
	rTempC = (Node *)malloc(sizeof(Node));
	rTemp = *root;
	rTempC = *root;

	while (fgets(line, sizeof(line), lFile) != NULL)		/* read a line */
	{
		pTemp = (List *)malloc(sizeof (List));
		strcpy(pTemp->line, line);
		pTemp->pNext = NULL;

		pTemp->pNext = pList;
		pList = pTemp;
	}

	while (pTemp->line[0] == 'm' || pTemp->line[0] == 'c')
	{
		strcpy(line, pTemp->line);

		tempSTR = strchr(line, '\n');
		if (tempSTR != NULL)
		{
			*tempSTR = '\0';
		}
		/*tempSTR = strtok(line, " ");
		strcpy(newLine, tempSTR);
		strcat(newLine, " ");
		tempSTR = strtok(NULL, " ");
		strcat(newLine, tempSTR);*/

		if (line[0] == 'm')
		{
			mkdir(&rTemp, &rTempC, line);
		}
		else
		{
			creat(&rTemp, &rTempC, line);
		}

		pTemp = pTemp->pNext;
	}

	/*pTemp = pList;
	printf("Node: %s", pTemp->line);*/
	fclose(lFile);
}

