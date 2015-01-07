#include "header.h"

void ls(Node **root, Node **rootC, char *line) //Lists files and directories
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

	if (strcmp(line, "ls") == 0)
	{
		if (rTempC->childPtr == NULL)
		{
			printf("directory is empty! \n");
		}
		else
		{
			rTempC = rTempC->childPtr;
			if (rTempC->fType == 'D')
			{
				printf("Directory: %s \n", rTempC->name);
			}
			else
			{
				printf("File: %s \n", rTempC->name);
			}

			while (rTempC->siblingPtr != NULL)
			{
				rTempC = rTempC->siblingPtr;

				if (rTempC->fType == 'D')
				{
					printf("Directory: %s \n", rTempC->name);
				}
				else
				{
					printf("File: %s \n", rTempC->name);
				}
			}
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
			rTempC = rTempC->childPtr;

			if (rTempC->childPtr == NULL)
			{
				printf("directory is empty! \n");
			}
			else
			{
				rTempC = rTempC->childPtr;
				if (rTempC->fType == 'D')
				{
					printf("Directory: %s \n", rTempC->name);
				}
				else
				{
					printf("File: %s \n", rTempC->name);
				}

				while (rTempC->siblingPtr != NULL)
				{
					rTempC = rTempC->siblingPtr;

					if (rTempC->fType == 'D')
					{
						printf("Directory: %s \n", rTempC->name);
					}
					else
					{
						printf("File: %s \n", rTempC->name);
					}
				}
			}
		}
		else if (strcmp(rTempC->childPtr->name, dirName) != 0)
		{
			rTempC = rTempC->childPtr;

			while (rTempC->siblingPtr != NULL)
			{
				rTempC = rTempC->siblingPtr;
				if (strcmp(rTempC->name, dirName) == 0 && rTempC->fType == 'D')
				{
					break;
				}
			}
			if (strcmp(rTempC->name, dirName) != 0)
			{
				printf("Path could not be found! \n");
			}
			else
			{
				if (rTempC->childPtr == NULL)
				{
					printf("directory is empty! \n");
				}
				else
				{
					if (rTempC->fType == 'D')
					{
						printf("Directory: %s \n", rTempC->name);
					}
					else
					{
						printf("File: %s \n", rTempC->name);
					}

					while (rTempC->siblingPtr != NULL)
					{
						rTempC = rTempC->siblingPtr;

						if (rTempC->fType == 'D')
						{
							printf("Directory: %s \n", rTempC->name);
						}
						else
						{
							printf("File: %s \n", rTempC->name);
						}
					}
				}
			}
		}
	}//FLAG
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
				{//INSERTION
					rTemp = rTemp->childPtr;

					if (rTemp->childPtr == NULL)
					{
						printf("directory is empty! \n");
					}
					else
					{
						rTemp = rTemp->childPtr;
						if (rTemp->fType == 'D')
						{
							printf("Directory: %s \n", rTemp->name);
						}
						else
						{
							printf("File: %s \n", rTemp->name);
						}

						while (rTemp->siblingPtr != NULL)
						{
							rTemp = rTemp->siblingPtr;

							if (rTemp->fType == 'D')
							{
								printf("Directory: %s \n", rTemp->name);
							}
							else
							{
								printf("File: %s \n", rTemp->name);
							}
						}
					}
				}//END
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
							break;
						}
					}
					if (strcmp(rTemp->name, dirName) != 0)
					{
						printf("Path could not be found! \n");
					}//INSERTION POINT
					else
					{
						rTemp = rTemp->childPtr;
						if (rTemp->fType == 'D')
						{
							printf("Directory: %s \n", rTemp->name);
						}
						else
						{
							printf("File: %s \n", rTemp->name);
						}

						while (rTemp->siblingPtr != NULL)
						{
							rTemp = rTemp->siblingPtr;

							if (rTemp->fType == 'D')
							{
								printf("Directory: %s \n", rTemp->name);
							}
							else
							{
								printf("File: %s \n", rTemp->name);
							}
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
					rTemp = rTemp->childPtr;

					if (rTemp->childPtr == NULL)
					{
						//printf("%s directory is empty! \n", rTemp->childPtr->name);
						printf("directory is empty! \n");
					}
					else
					{
						rTemp = rTemp->childPtr;
						if (rTemp->fType == 'D')
						{
							printf("Directory: %s \n", rTemp->name);
						}
						else
						{
							printf("File: %s \n", rTemp->name);
						}

						while (rTemp->siblingPtr != NULL)
						{
							rTemp = rTemp->siblingPtr;

							if (rTemp->fType == 'D')
							{
								printf("Directory: %s \n", rTemp->name);
							}
							else
							{
								printf("File: %s \n", rTemp->name);
							}
						}
					}
				}
				else
				{
					rTemp = rTemp->childPtr;

					while (rTemp->siblingPtr != NULL)
					{
						rTemp = rTemp->siblingPtr;
						if (strcmp(rTemp->name, dirName) == 0 && rTemp->fType == 'D')
						{
							break;
						}
					}
					if (strcmp(rTemp->name, dirName) != 0)
					{
						printf("Path could not be found! \n");
					}
					else
					{
						rTemp = rTemp->childPtr;
						if (rTemp->fType == 'D')
						{
							printf("Directory: %s \n", rTemp->name);
						}
						else
						{
							printf("File: %s \n", rTemp->name);
						}

						while (rTemp->siblingPtr != NULL)
						{
							rTemp = rTemp->siblingPtr;

							if (rTemp->fType == 'D')
							{
								printf("Directory: %s \n", rTemp->name);
							}
							else
							{
								printf("File: %s \n", rTemp->name);
							}
						}
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
					rTempC = rTempC->childPtr;

					if (rTempC->childPtr == NULL)
					{
						printf("directory is empty! \n");
					}
					else
					{
						rTempC = rTempC->childPtr;
						if (rTempC->fType == 'D')
						{
							printf("Directory: %s \n", rTempC->name);
						}
						else
						{
							printf("File: %s \n", rTempC->name);
						}

						while (rTempC->siblingPtr != NULL)
						{
							rTempC = rTempC->siblingPtr;

							if (rTempC->fType == 'D')
							{
								printf("Directory: %s \n", rTempC->name);
							}
							else
							{
								printf("File: %s \n", rTempC->name);
							}
						}
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
						rTempC = rTempC->siblingPtr;
						if (strcmp(rTempC->name, dirName) == 0 && rTempC->fType == 'D')
						{
							break;
						}
					}
					if (strcmp(rTempC->name, dirName) != 0)
					{
						printf("Path could not be found! \n");
					}
					else
					{
						rTempC = rTempC->childPtr;
						if (rTempC->fType == 'D')
						{
							printf("Directory: %s \n", rTempC->name);
						}
						else
						{
							printf("File: %s \n", rTempC->name);
						}

						while (rTempC->siblingPtr != NULL)
						{
							rTempC = rTempC->siblingPtr;

							if (rTempC->fType == 'D')
							{
								printf("Directory: %s \n", rTempC->name);
							}
							else
							{
								printf("File: %s \n", rTempC->name);
							}
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
					rTempC = rTempC->childPtr;

					if (rTempC->childPtr == NULL)
					{
						//printf("%s directory is empty! \n", rTempC->childPtr->name);
						printf("directory is empty! \n");
					}
					else
					{
						rTempC = rTempC->childPtr;
						if (rTempC->fType == 'D')
						{
							printf("Directory: %s \n", rTempC->name);
						}
						else
						{
							printf("File: %s \n", rTempC->name);
						}

						while (rTempC->siblingPtr != NULL)
						{
							rTempC = rTempC->siblingPtr;

							if (rTempC->fType == 'D')
							{
								printf("Directory: %s \n", rTempC->name);
							}
							else
							{
								printf("File: %s \n", rTempC->name);
							}
						}
					}
				}
				else
				{
					rTempC = rTempC->childPtr;

					while (rTempC->siblingPtr != NULL)
					{
						rTempC = rTempC->siblingPtr;
						if (strcmp(rTempC->name, dirName) == 0 && rTempC->fType == 'D')
						{
							break;
						}
					}
					if (strcmp(rTempC->name, dirName) != 0)
					{
						printf("Path could not be found! \n");
					}
					else
					{
						rTempC = rTempC->childPtr;
						if (rTempC->fType == 'D')
						{
							printf("Directory: %s \n", rTempC->name);
						}
						else
						{
							printf("File: %s \n", rTempC->name);
						}

						while (rTempC->siblingPtr != NULL)
						{
							rTempC = rTempC->siblingPtr;

							if (rTempC->fType == 'D')
							{
								printf("Directory: %s \n", rTempC->name);
							}
							else
							{
								printf("File: %s \n", rTempC->name);
							}
						}
					}
				}
			}
		}
	}
}