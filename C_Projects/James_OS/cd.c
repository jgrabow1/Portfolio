#include "header.h"

void cd(Node **root, Node **rootC, char *line, char *currentPath) //Changes directory
{
	Node *rTemp = NULL;
	Node *rTempC = NULL;
	char lineBUFFER[128], lineBUFFER2[128], lineBUFFER3[128], lineBUFFER4[128], comparison[128], dirName[64], locationName[64];
	char *tempSTR;
	int depth = 0, error = 0, currentDepth = 0;

	rTemp = (Node *)malloc(sizeof(Node));
	rTempC = (Node *)malloc(sizeof(Node));
	rTemp = *root;
	rTempC = *rootC;

	strcpy(lineBUFFER, line);
	strcpy(lineBUFFER2, line);
	strcpy(lineBUFFER3, line);
	strcpy(lineBUFFER4, line);

	depth = determineDepth(lineBUFFER3);
	tempSTR = strtok(lineBUFFER, " ");
	tempSTR = strtok(NULL, " ");
	strcpy(comparison, tempSTR);

	if (strcmp(comparison, "..") == 0)
	{
		if (strcmp(currentPath, "/") == 0)
		{
			printf("Sorry! You are already in the root directory! \n");
		}
		else
		{
			printf("This function has not yet been implemented! \n");
		}
	}
	else if (strcmp(comparison, "/") == 0)
	{
		while (rTempC->parentPtr != NULL)
		{
			rTempC = rTempC->parentPtr;
			*rootC = rTempC;
			strcpy(currentPath, "/");
		}
	}
	else if (depth == 0)
	{
		getName3(lineBUFFER2, dirName, locationName, depth);

		if (rTempC->childPtr == NULL)
		{
			printf("Path does not exist! \n");
		}
		else if (strcmp(rTempC->childPtr->name, dirName) == 0 && rTempC->childPtr->fType != 'D')
		{
			printf("Location is a file, not a directory! \n");
		}
		else if (strcmp(rTempC->childPtr->name, dirName) == 0 && rTempC->childPtr->fType == 'D')
		{
			if (strcmp(rTempC->name, "/") != 0)
			{
				strcat(currentPath, "/");
			}
			strcat(currentPath, comparison);
			rTempC = rTempC->childPtr;
			*rootC = rTempC;
		}
		else if (strcmp(rTempC->childPtr->name, dirName) != 0)
		{
			rTempC = rTempC->childPtr;

			while (rTempC->siblingPtr != NULL)
			{
				rTempC = rTempC->siblingPtr;
				if (strcmp(rTempC->name, dirName) == 0 && rTempC->fType == 'D')
				{
					if (strcmp(rTempC->name, "/") != 0)
					{
						strcat(currentPath, "/");
					}
					strcat(currentPath, comparison);
					*rootC = rTempC;
					break;
				}
			}
			if (strcmp(rTempC->name, dirName) != 0)
			{
				rTempC = rTempC->parentPtr;
				printf("Path could not be found! \n");
			}
		}
	}
	else if (line[3] == '/')
	{
		getName(lineBUFFER2, dirName, locationName, depth); //BEGINNING OF LINE[3] WITH SLASH

		if (depth == 1)
		{
			tempSTR = strtok(lineBUFFER4, "/");
			tempSTR = strtok(NULL, "/");
			if (rTemp->childPtr == NULL)
			{
				printf("Path does not exist! \n");
			}
			else
			{
				if (strcmp(rTemp->childPtr->name, dirName) == 0 && rTemp->childPtr->fType == 'D')
				{
					rTempC = rTemp->childPtr;
					*rootC = rTempC;
					strcpy(currentPath, comparison);
				}
				else if (strcmp(rTemp->childPtr->name, dirName) == 0 && rTemp->childPtr->fType != 'D')
				{
					printf("Error! File with same name already exists! \n");
				}
				else
				{
					rTemp = rTemp->childPtr;

					while (rTemp->siblingPtr != NULL)
					{
						rTemp = rTemp->siblingPtr;
						if (strcmp(rTemp->name, dirName) == 0 && rTemp->fType == 'D')
						{
							strcpy(currentPath, comparison);
							*rootC = rTemp;
							break;
						}
					}
					if (strcmp(rTemp->name, dirName) != 0)
					{
						printf("Path could not be found! \n");
					}
				}
			}
		}
		else   //DEPTH IS EQUAL TO MORE THAN 1
		{
			tempSTR = strtok(lineBUFFER4, "/");
			while (currentDepth < (depth - 1))
			{
				tempSTR = strtok(NULL, "/");

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
			else if (strcmp(rTemp->name, locationName) == 0) //FOUND THE LOCATION FOR TARGET DIRECTORY!
			{
				if (rTemp->childPtr == NULL)
				{
					printf("Path does not exist! \n");
				}
				else if (strcmp(rTemp->childPtr->name, dirName) == 0 && rTemp->childPtr->fType != 'D')
				{
					printf("Node with same name already exists! \n");
				}
				else if (strcmp(rTemp->childPtr->name, dirName) == 0 && rTemp->childPtr->fType == 'D')
				{
					rTempC = rTemp->childPtr;
					*rootC = rTempC;
					strcpy(currentPath, comparison);
				}
				else
				{
					rTemp = rTemp->childPtr;

					while (rTemp->siblingPtr != NULL)
					{
						rTemp = rTemp->siblingPtr;
						if (strcmp(rTemp->name, dirName) == 0 && rTemp->fType == 'D')
						{
							strcpy(currentPath, comparison);
							*rootC = rTemp;
							break;
						}
					}
					if (strcmp(rTemp->name, dirName) != 0)
					{
						printf("Path could not be found! \n");
					}
				}
			}
		}
	} //END OF LINE[3] WITH SLASH
	else
	{
		getName2(lineBUFFER2, dirName, locationName, depth);
		if (depth == 0)
		{
			tempSTR = strtok(lineBUFFER4, " ");
			tempSTR = strtok(NULL, "/");
			if (rTempC->childPtr == NULL)
			{
				printf("Path does not exist! \n");
			}
			else
			{
				if (strcmp(rTempC->childPtr->name, dirName) == 0 && rTempC->childPtr->fType == 'D')
				{
					if (strcmp(currentPath, "/") != 0)
					{
						strcat(currentPath, "/");
					}
					rTempC = rTempC->childPtr;
					*rootC = rTempC;
					strcat(currentPath, comparison);
				}
				else if (strcmp(rTempC->childPtr->name, dirName) == 0 && rTempC->childPtr->fType != 'D')
				{
					printf("Error! File with same name already exists! \n");
				}
				else
				{
					rTempC = rTempC->childPtr;

					while (rTempC->siblingPtr != NULL)
					{
						rTempC = rTempC->siblingPtr;
						if (strcmp(rTempC->name, dirName) == 0 && rTempC->fType == 'D')
						{
							if (strcmp(rTempC->name, "/") != 0)
							{
								strcat(currentPath, "/");
							}
							strcat(currentPath, comparison);
							*rootC = rTempC;
							break;
						}
					}
					if (strcmp(rTempC->name, dirName) != 0)
					{
						printf("Path could not be found! \n");
					}
				}
			}
		}
		else   //DEPTH IS EQUAL TO MORE THAN 1
		{
			tempSTR = strtok(lineBUFFER4, " ");
			while (currentDepth < depth)
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
			else if (strcmp(rTempC->name, locationName) == 0) //FOUND THE LOCATION FOR TARGET DIRECTORY!
			{
				if (rTempC->childPtr == NULL)
				{
					printf("Path does not exist! \n");
				}
				else if (strcmp(rTempC->childPtr->name, dirName) == 0 && rTempC->childPtr->fType != 'D')
				{
					printf("Node with same name already exists! \n");
				}
				else if (strcmp(rTempC->childPtr->name, dirName) == 0 && rTempC->childPtr->fType == 'D')
				{
					if (strcmp(currentPath, "/") != 0)
					{
						strcat(currentPath, "/");
					}
					rTempC = rTempC->childPtr;
					*rootC = rTempC;
					strcat(currentPath, comparison);
				}
				else
				{
					rTempC = rTempC->childPtr;

					while (rTempC->siblingPtr != NULL)
					{
						rTempC = rTempC->siblingPtr;
						if (strcmp(rTempC->name, dirName) == 0 && rTempC->fType == 'D')
						{
							if (strcmp(rTempC->name, "/") != 0)
							{
								strcat(currentPath, "/");
							}
							strcat(currentPath, comparison);
							*rootC = rTempC;
							break;
						}
					}
					if (strcmp(rTempC->name, dirName) != 0)
					{
						printf("Path could not be found! \n");
					}
				}
			}
		}
	}
	/*printf ("Line in CD: %c \n", line);
	system("pause"); */
}
