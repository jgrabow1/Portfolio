#include "header.h"

void save(Node **root, Node **rootC) //Saves state of file system to text file
{
	Node *rTemp = NULL;
	Node *rTempC = NULL;
	char lineBUFFER[128], lineBUFFER2[128];
	char pathInput[128], commandInput[128], commandInput2[128];
	char *tempSTR;
	int count = 0;

	FILE * sFile;
	sFile = fopen("save.txt", "w");

	rTemp = (Node *)malloc(sizeof(Node));
	rTempC = (Node *)malloc(sizeof(Node));
	rTemp = *root;
	rTempC = *root;

	/*strcpy(pathInput, "gregeg");
	strcpy(pathInput, "/");
	printf("PathInput: %s \n", pathInput);*/

	while (1)
	{
		strcpy(pathInput, "/");
		if (rTemp->childPtr == NULL)
		{
			break;
		}
		while (rTemp->childPtr != NULL)
		{
			rTemp = rTemp->childPtr;

			if (rTemp->fType == 'D')
			{
				if (count > 0)
				{
					strcat(pathInput, "/");
				}
				strcat(pathInput, toupper(rTemp->name));
				count++;
			}
			else
			{
				if (count > 0)
				{
					strcat(pathInput, "/");
				}
				strcat(pathInput, tolower(rTemp->name));
				count++;
			}
		}
		if (rTemp->fType == 'D')
		{
			/*strcat(pathInput, "/");
			strcat(pathInput, toupper(rTempC->name));*/

			if (sFile != NULL)
			{
				fprintf(sFile, "mkdir %s\n", pathInput);
			}
			strcpy(commandInput, "rmdir ");
			strcat(commandInput, pathInput);

			rTemp = *root;
			rmdir(&rTemp, &rTempC, commandInput);
		}
		else
		{
			/*strcat(pathInput, "/");
			strcat(pathInput, tolower(rTempC->name));*/

			if (sFile != NULL)
			{
				fprintf(sFile, "creat %s\n", pathInput);
			}
			strcpy(commandInput2, "rm ");
			strcat(commandInput2, pathInput);

			rTemp = *root;
			rm(&rTemp, &rTempC, commandInput2);
		}
		count = 0;
	}

	fclose(sFile);
}
