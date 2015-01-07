#include "header.h"

void rmdir(Node **root, Node **rootC, char *line) //Removes directory.
{
	Node *rTemp = NULL;
	Node *rTempC = NULL;
	char lineBUFFER[128], lineBUFFER2[128], lineBUFFER3[128], lineBUFFER4[128], dirName[64], locationName[64];
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

	if (depth == 0)
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
			if (rTempC->childPtr->childPtr != NULL)
			{
				printf("Directory is linked to other files or directories and cannot be removed! \n");
			}
			else
			{
				rTemp = rTempC->childPtr->siblingPtr;

				free(rTempC->childPtr);
				rTempC->childPtr = rTemp;
				*rootC = rTempC;
			}
		}
		else if (strcmp(rTempC->childPtr->name, dirName) != 0)
		{
			rTempC = rTempC->childPtr;

			while (rTempC->siblingPtr != NULL)
			{
				if (strcmp(rTempC->siblingPtr, dirName) == 0 && rTempC->fType == 'D')
				{
					break;
				}
				rTempC = rTempC->siblingPtr;
			}
			if (strcmp(rTempC->siblingPtr, dirName) != 0)
			{
				printf("Path could not be found! \n");
			}
			else
			{
				if (rTempC->siblingPtr->childPtr != NULL)
				{
					printf("Directory is linked to other files or directories and cannot be removed! \n");
				}
				else
				{
					rTemp = rTempC->siblingPtr->siblingPtr;

					free(rTempC->siblingPtr);
					rTempC->siblingPtr = rTemp;
					while (rTempC->parentPtr != NULL)
					{
						rTempC = rTempC->parentPtr;
					}
					*rootC = rTempC;
				}
			}
		}
	}
	else if (line[6] == '/')
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
				{//INSERTION
					if (rTemp->childPtr->childPtr != NULL)
					{
						printf("Directory is linked to other files or directories and cannot be removed! \n");
					}
					else
					{
						rTempC = rTemp->childPtr->siblingPtr;

						free(rTemp->childPtr);
						rTemp->childPtr = rTempC;
						*root = rTemp;
					}
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
						if (strcmp(rTemp->siblingPtr, dirName) == 0 && rTemp->fType == 'D')
						{
							break;
						}
						rTemp = rTemp->siblingPtr;
					}
					if (strcmp(rTemp->siblingPtr, dirName) != 0)
					{
						printf("Path could not be found! \n");
					}
					else
					{
						if (rTemp->siblingPtr->childPtr != NULL)
						{
							printf("Directory is linked to other files or directories and cannot be removed! \n");
						}
						else
						{
							rTempC = rTemp->siblingPtr->siblingPtr;

							free(rTemp->siblingPtr);
							rTemp->siblingPtr = rTempC;
							while (rTemp->parentPtr != NULL)
							{
								rTemp = rTemp->parentPtr;
							}
							*root = rTemp;
						}
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
					if (rTemp->childPtr->childPtr != NULL)
					{
						printf("Directory is linked to other files or directories and cannot be removed! \n");
					}
					else
					{
						rTempC = rTemp->childPtr->siblingPtr;

						free(rTemp->childPtr);
						rTemp->childPtr = rTempC;
						while (rTemp->parentPtr != NULL)
						{
							rTemp = rTemp->parentPtr;
						}
						*root = rTemp;
					}
				}
				else
				{
					rTemp = rTemp->childPtr;

					while (rTemp->siblingPtr != NULL)
					{
						if (strcmp(rTemp->siblingPtr, dirName) == 0 && rTemp->fType == 'D')
						{
							break;
						}
						rTemp = rTemp->siblingPtr;
					}
					if (strcmp(rTemp->siblingPtr, dirName) != 0)
					{
						printf("Path could not be found! \n");
					}
					else
					{
						if (rTemp->siblingPtr->childPtr != NULL)
						{
							printf("Directory is linked to other files or directories and cannot be removed! \n");
						}
						else
						{
							rTempC = rTemp->siblingPtr->siblingPtr;

							free(rTemp->siblingPtr);
							rTemp->siblingPtr = rTempC;
							while (rTemp->parentPtr != NULL)
							{
								rTemp = rTemp->parentPtr;
							}
							*root = rTemp;
						}
					}
				}
			}
		}
	}
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
					if (rTempC->childPtr->childPtr != NULL)
					{
						printf("Directory is linked to other files or directories and cannot be removed! \n");
					}
					else
					{
						rTemp = rTempC->childPtr->siblingPtr;

						free(rTempC->childPtr);
						rTempC->childPtr = rTemp;
						while (rTempC->parentPtr != NULL)
						{
							rTempC = rTempC->parentPtr;
						}
						*root = rTempC;
					}
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
						if (strcmp(rTempC->siblingPtr, dirName) == 0 && rTempC->fType == 'D')
						{
							break;
						}
						rTempC = rTempC->siblingPtr;
					}
					if (strcmp(rTempC->siblingPtr, dirName) != 0)
					{
						printf("Path could not be found! \n");
					}
					else
					{
						if (rTempC->siblingPtr->childPtr != NULL)
						{
							printf("Directory is linked to other files or directories and cannot be removed! \n");
						}
						else
						{
							rTemp = rTempC->siblingPtr->siblingPtr;

							free(rTempC->siblingPtr);
							rTempC->siblingPtr = rTemp;
							while (rTempC->parentPtr != NULL)
							{
								rTempC = rTempC->parentPtr;
							}
							*root = rTempC;
						}
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
					if (rTempC->childPtr->childPtr != NULL)
					{
						printf("Directory is linked to other files or directories and cannot be removed! \n");
					}
					else
					{
						rTemp = rTempC->childPtr->siblingPtr;

						free(rTempC->childPtr);
						rTempC->childPtr = rTemp;
						while (rTempC->parentPtr != NULL)
						{
							rTempC = rTempC->parentPtr;
						}
						*root = rTempC;
					}
				}
				else
				{
					rTempC = rTempC->childPtr;

					while (rTempC->siblingPtr != NULL)
					{
						if (strcmp(rTempC->siblingPtr, dirName) == 0 && rTempC->fType == 'D')
						{
							break;
						}
						rTempC = rTempC->siblingPtr;
					}
					if (strcmp(rTempC->siblingPtr, dirName) != 0)
					{
						printf("Path could not be found! \n");
					}
					else
					{
						if (rTempC->siblingPtr->childPtr != NULL)
						{
							printf("Directory is linked to other files or directories and cannot be removed! \n");
						}
						else
						{
							rTemp = rTempC->siblingPtr->siblingPtr;

							free(rTempC->siblingPtr);
							rTempC->siblingPtr = rTemp;
							while (rTempC->parentPtr != NULL)
							{
								rTempC = rTempC->parentPtr;
							}
							*root = rTempC;
						}
					}
				}
			}
		}
	}
}
