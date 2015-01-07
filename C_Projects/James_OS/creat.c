#include "header.h"

void creat(Node **root, Node **rootC, char *line) //Creates a file
{
	Node *pMem = NULL;
	Node *rTemp = NULL;
	Node *rTempC = NULL;
	char lineBUFFER[128], lineBUFFER2[128], dirName[64], locationName[64], testSTR[128];
	char *tempSTR;
	int depth = 0, currentDepth = 0, comparison = 0, error = 0;

	pMem = (Node *)malloc(sizeof(Node));
	rTemp = (Node *)malloc(sizeof(Node));
	rTempC = (Node *)malloc(sizeof(Node));
	rTemp = *root;
	rTempC = *rootC;

	strcpy(lineBUFFER, line);
	strcpy(lineBUFFER2, line);
	depth = determineDepth(line);
	/*printf("Depth: %d \n", depth);
	system("pause");*/

	//getName(lineBUFFER2, dirName, locationName, depth);

	/*printf("Dir Name: %s \n", dirName);
	printf("Loc Name: %s \n", locationName);*/

	if (line[6] == '/')
	{
		getName(lineBUFFER2, dirName, locationName, depth);
		tempSTR = strtok(lineBUFFER, "/");

		if (depth == 1)
		{
			tempSTR = strtok(NULL, "/");

			if (rTemp->childPtr == NULL)
			{
				pMem->childPtr = NULL;
				pMem->fType = 'F';
				strcpy(pMem->name, dirName);
				pMem->parentPtr = rTemp;
				pMem->siblingPtr = NULL;

				rTemp->childPtr = pMem;
				*root = rTemp;
			}
			else
			{
				if (strcmp(rTemp->childPtr->name, dirName) == 0 && rTemp->childPtr->fType == 'F')
				{
					printf("File already exists! \n");
				}
				else if (strcmp(rTemp->childPtr->name, dirName) == 0 && rTemp->childPtr->fType != 'F')
				{
					printf("Error! Directory with same name already exists! \n");
				}
				else
				{
					pMem->childPtr = NULL;
					pMem->fType = 'F';
					strcpy(pMem->name, dirName);
					pMem->parentPtr = rTemp;
					pMem->siblingPtr = NULL;

					rTemp = rTemp->childPtr;

					while (rTemp->siblingPtr != NULL)
					{
						rTemp = rTemp->siblingPtr;
						if (strcmp(rTemp->name, dirName) == 0 && rTemp->fType == 'F')
						{
							comparison++;
						}
					}
					if (comparison == 0)
					{
						rTemp->siblingPtr = pMem;
						rTemp = rTemp->parentPtr;
						*root = rTemp;
					}
					else
					{
						printf("File already exists! \n");
					}
					comparison = 0;
				}
			}
		}
		else   //DEPTH IS EQUAL TO MORE THAN 1
		{
			while (currentDepth < (depth - 1))
			{
				tempSTR = strtok(NULL, "/");

				//strcpy(testSTR, tempSTR);

				if (strcmp(rTemp->childPtr->name, tempSTR) == 0 && rTemp->childPtr->fType == 'D')
				{
					rTemp = rTemp->childPtr;
				}
				else if (rTemp->childPtr->name == NULL)
				{
					printf("Invalid path! \n");
				}
				else if (strcmp(rTemp->childPtr->name, tempSTR) != 0)
				{
					rTemp = rTemp->childPtr;

					while (1)
					{
						if (strcmp(rTemp->name, tempSTR) == 0)
						{
							break;
						}
						else if (rTemp->siblingPtr == NULL)
						{
							break;
						}
						rTemp = rTemp->siblingPtr;
					}
					if (strcmp(rTemp->name, tempSTR) != 0)
					{
						error++;
					}
				}
				if (error > 0)
				{
					printf("Invalid path! \n");
					break;
				}
				currentDepth++;
			}
			if (strcmp(rTemp->name, tempSTR) != 0)
			{
				printf("Invalid path! \n");
			}
			else if (strcmp(rTemp->name, locationName) == 0) //FOUND THE LOCATION FOR NEW DIRECTORY!
			{//FLAG
				if (rTemp->childPtr == NULL)
				{
					pMem->childPtr = NULL;
					pMem->fType = 'F';
					strcpy(pMem->name, dirName);
					pMem->parentPtr = rTemp;
					pMem->siblingPtr = NULL;

					rTemp->childPtr = pMem;
					while (rTemp->parentPtr != NULL)
					{
						rTemp = rTemp->parentPtr;
					}
					*root = rTemp;
				}
				else if (strcmp(rTemp->childPtr->name, dirName) == 0)
				{
					printf("Node with same name already exists! \n");
				}
				else
				{
					pMem->childPtr = NULL;
					pMem->fType = 'F';
					strcpy(pMem->name, dirName);
					pMem->parentPtr = rTemp;
					pMem->siblingPtr = NULL;

					rTemp = rTemp->childPtr;

					while (rTemp->siblingPtr != NULL)
					{
						rTemp = rTemp->siblingPtr;
						if (strcmp(rTemp->name, dirName) == 0 && rTemp->fType == 'F')
						{
							comparison++;
						}
					}
					if (comparison == 0)
					{
						rTemp->siblingPtr = pMem;
						while (rTemp->parentPtr != NULL)
						{
							rTemp = rTemp->parentPtr;
						}
						*root = rTemp;
					}
					else
					{
						printf("File already exists! \n");
					}
					comparison = 0;
				}
			}//FLAG
		} //END OF DEPTH > 1 LOOP
	}
	else if (depth >= 1) //MKDIR WITHOUT SLASH
	{
		getName2(lineBUFFER2, dirName, locationName, depth);
		tempSTR = strtok(lineBUFFER, " ");

		if (depth == 0) //WITHOUT SLASH DEPTH IS EQUAL TO ZERO
		{
			tempSTR = strtok(NULL, "/");

			if (rTempC->childPtr == NULL)
			{
				pMem->childPtr = NULL;
				pMem->fType = 'D';
				strcpy(pMem->name, dirName);
				pMem->parentPtr = rTempC;
				pMem->siblingPtr = NULL;

				rTempC->childPtr = pMem;
				*rootC = rTempC;
			}
			else
			{
				if (strcmp(rTempC->childPtr->name, dirName) == 0 && rTempC->childPtr->fType == 'F')
				{
					printf("Directory already exists! \n");
				}
				else if (strcmp(rTempC->childPtr->name, dirName) == 0 && rTempC->childPtr->fType != 'F')
				{
					printf("Error! File with same name already exists! \n");
				}
				else
				{
					pMem->childPtr = NULL;
					pMem->fType = 'F';
					strcpy(pMem->name, dirName);
					pMem->parentPtr = rTempC;
					pMem->siblingPtr = NULL;

					rTempC = rTempC->childPtr;

					while (rTempC->siblingPtr != NULL)
					{
						rTempC = rTempC->siblingPtr;
						if (strcmp(rTempC->name, dirName) == 0 && rTempC->fType == 'F')
						{
							comparison++;
						}
					}
					if (comparison == 0)
					{
						rTempC->siblingPtr = pMem;
						rTempC = rTempC->parentPtr;
						*root = rTempC;
					}
					else
					{
						printf("File already exists! \n");
					}
					comparison = 0;
				}
			}
		}
		else   //DEPTH IS EQUAL TO MORE THAN 1
		{
			while (currentDepth < (depth))
			{
				tempSTR = strtok(NULL, "/");

				if (strcmp(rTempC->childPtr->name, tempSTR) == 0 && rTempC->childPtr->fType == 'D')
				{
					rTempC = rTempC->childPtr;
				}
				else if (rTempC->childPtr->name == NULL)
				{
					printf("Invalid path! \n");
				}
				else if (strcmp(rTempC->childPtr->name, tempSTR) != 0)
				{
					rTempC = rTempC->childPtr;

					while (1)
					{
						if (strcmp(rTempC->name, tempSTR) == 0)
						{
							break;
						}
						else if (rTempC->siblingPtr == NULL)
						{
							break;
						}
						rTempC = rTempC->siblingPtr;
					}
					if (strcmp(rTempC->name, tempSTR) != 0)
					{
						error++;
					}
				}
				if (error > 0)
				{
					printf("Invalid path! \n");
					break;
				}
				currentDepth++;
			}
			if (strcmp(rTempC->name, tempSTR) != 0)
			{
				printf("Invalid path! \n");
			}
			else if (strcmp(rTempC->name, locationName) == 0) //FOUND THE LOCATION FOR NEW DIRECTORY!
			{
				if (rTempC->childPtr == NULL)
				{
					pMem->childPtr = NULL;
					pMem->fType = 'F';
					strcpy(pMem->name, dirName);
					pMem->parentPtr = rTempC;
					pMem->siblingPtr = NULL;

					rTempC->childPtr = pMem;
					while (rTempC->parentPtr != NULL)
					{
						rTempC = rTempC->parentPtr;
					}
					*rootC = rTempC;
				}
				else if (strcmp(rTempC->childPtr->name, dirName) == 0)
				{
					printf("Node with same name already exists! \n");
				}
				else
				{
					pMem->childPtr = NULL;
					pMem->fType = 'F';
					strcpy(pMem->name, dirName);
					pMem->parentPtr = rTempC;
					pMem->siblingPtr = NULL;

					rTempC = rTempC->childPtr;

					while (rTempC->siblingPtr != NULL)
					{
						rTempC = rTempC->siblingPtr;
						if (strcmp(rTempC->name, dirName) == 0 && rTempC->fType == 'F')
						{
							comparison++;
						}
					}
					if (comparison == 0)
					{
						rTempC->siblingPtr = pMem;
						while (rTempC->parentPtr != NULL)
						{
							rTempC = rTempC->parentPtr;
						}
						*rootC = rTempC;
					}
					else
					{
						printf("Directory already exists! \n");
					}
					comparison = 0;
				}
			}
		}
	} //END OF MKDIR WITHOUT FIRST SLASH
	else //MKDIR ZERO SLASH
	{
		getName3(lineBUFFER2, dirName, locationName, depth);
		tempSTR = strtok(lineBUFFER, " ");

		if (depth == 0)
		{
			tempSTR = strtok(NULL, " ");

			if (rTempC->childPtr == NULL)
			{
				pMem->childPtr = NULL;
				pMem->fType = 'F';
				strcpy(pMem->name, dirName);
				pMem->parentPtr = rTempC;
				pMem->siblingPtr = NULL;

				rTempC->childPtr = pMem;
				*rootC = rTempC;
			}
			else
			{
				if (strcmp(rTempC->childPtr->name, dirName) == 0 && rTempC->childPtr->fType == 'F')
				{
					printf("File already exists! \n");
				}
				else if (strcmp(rTempC->childPtr->name, dirName) == 0 && rTempC->childPtr->fType != 'F')
				{
					printf("Error! File with same name already exists! \n");
				}
				else
				{
					pMem->childPtr = NULL;
					pMem->fType = 'F';
					strcpy(pMem->name, dirName);
					pMem->parentPtr = rTempC;
					pMem->siblingPtr = NULL;

					rTempC = rTempC->childPtr;

					while (rTempC->siblingPtr != NULL)
					{
						rTempC = rTempC->siblingPtr;
						if (strcmp(rTempC->name, dirName) == 0 && rTempC->fType == 'F')
						{
							comparison++;
						}
					}
					if (comparison == 0)
					{
						rTempC->siblingPtr = pMem;
						rTempC = rTempC->parentPtr;
						*rootC = rTempC;
					}
					else
					{
						printf("File already exists! \n");
					}
					comparison = 0;
				}
			}
		}
	}
	//system("pause");
	currentDepth = 0;
}

