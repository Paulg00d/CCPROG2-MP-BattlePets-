#include <stdio.h>
#include <string.h>
#include "CCPROG2_MP_(BattlePets)_Functions.h"

void CompetdiumMenu(Grid PetList[], int nPetCount){
	int nChoice;
	
	do{
		printf("+------------------------------------+\n");
		printf("|  Choose what you want to do with   |\n");
		printf("|            the pets                |\n");
		printf("+-----------+------------------------+\n");
		printf("|     1     |    View BattlePets/s   |\n");
		printf("+-----------+------------------------+\n");
		printf("|     2     |      Add BattlePet     |\n");
		printf("+-----------+------------------------+\n");
		printf("|     3     |      Edit BattlePet    |\n");
		printf("+-----------+------------------------+\n");
		printf("|     4     |    Delete BattlePet    |\n");
		printf("+-----------+------------------------+\n");
		printf("|     5     |      Save Roster       |\n");
		printf("+-----------+------------------------+\n");
		printf("|     0     |          Exit          |\n");
		printf("+-----------+------------------------+\n");
		printf("> ");
		scanf("%d",&nChoice);
		
		if(nChoice != 0){
			switch(nChoice){
			case 1:
				PrintBattlePets(PetList, nPetCount);
				break;
			
			case 2:
				PrintBattlePets(PetList, nPetCount);
				AddBattlePets(PetList, &nPetCount);
				break;
		
			case 3:
				PrintBattlePets(PetList, nPetCount);
				EditBattlePets(PetList, nPetCount);
				break;
			
			case 4:
				PrintBattlePets(PetList, nPetCount);
				DeleteBattlePets(PetList, &nPetCount);
				break;
				
			case 5:
				PrintBattlePets(PetList, nPetCount);
				SaveRoster(PetList, nPetCount);
				break;
			}
		}
	}while(nChoice != 0);
}

/**
 * The function PrintBattlePets prints all the pets stored in Petlist
 * @param PetList is an array of structs containing the information 
 * @pre Player1Roster and Player2Roster already have the relevant pet information each, and Player1Name and Player2Name already contain the names of the players, nPlayerCount is at least 0
 */
void PrintBattlePets(Grid PetList[], int nPetCount){
	for(int i = 0; i < nPetCount && i < MAX_PETS; i++){
		printf("%d.\n", i + 1);
		printf("Name: %s\n", PetList[i].szPetName);
		printf("Element: %s\n", PetList[i].szElement);
		printf("Description: %s\n", PetList[i].szDescription);
		printf("Match count: %d\n\n", PetList[i].nMatchCount);
	}
}

void AddBattlePets(Grid PetList[], int *pPetCount){
	int nRemainingPets = MAX_PETS - *pPetCount;
	int nChoice;
	int nSameName;
	char szTempName[37];
	char cBuffer;
	FILE *fp;
	
	do{
		printf("|---%d more pets can be added to Competdium---|\n", nRemainingPets);
		printf("|---There are now %d pets in Competdium---|\n", *pPetCount);
		do{
			nSameName = 0;
			printf("Enter the name: ");
			scanf("%s", szTempName);
			
			for(int j = 0; j < *pPetCount; j++)
				if(strcmp(szTempName, PetList[j].szPetName) == 0)
					nSameName = 1;
					
			if(nSameName)
				printf("This pet already exists.\n");
		}while(nSameName);
		strcpy(PetList[*pPetCount].szPetName, szTempName);
		scanf("%c", &cBuffer);
		printf("Enter the element: ");
		scanf("%s", PetList[*pPetCount].szElement);
		scanf("%c", &cBuffer);
		printf("Enter the description: ");
		scanf("%[^\n]", PetList[*pPetCount].szDescription);
		PetList[*pPetCount].nMatchCount = 0;
		
		(*pPetCount)++;
		nRemainingPets--;
		
		printf("Would you like to enter another pet? (1 - yes, 2 - no)\n");
		printf("> ");
		scanf("%d", &nChoice);
	}while(nChoice == 1 && nRemainingPets > 0);
	
	fp = fopen("competdium.txt", "w");
	for(int i = 0; i < *pPetCount && i < MAX_PETS; i++){
		fprintf(fp, "%s\n", PetList[i].szPetName);
		fprintf(fp, "%s\n", PetList[i].szElement);
		fprintf(fp, "%s\n", PetList[i].szDescription);
		fprintf(fp, "%d\n\n", PetList[i].nMatchCount);
	}
	
	fclose(fp);
}

void EditBattlePets(Grid PetList[], int nPetCount){
	FILE *fp;
	int nChoice;
	int index;
	int nSameName;
	char szTempName[37];
	char cBuffer;
	
	do{
		printf("Please input the number for the pokemon you wish to edit:");
		scanf("%d", &index);
		index--;
		
		printf("|---Editing %s---|\n", PetList[index].szPetName);
		printf("Do you wish to edit its name? (1 - yes, 2 - no)\n");
		printf("> ");
		scanf("%d", &nChoice);
		scanf("%c", &cBuffer);
		if(nChoice == 1){
			printf("Current name: %s\n",PetList[index].szPetName);
			do{
				nSameName = 0;
				printf("New name: ");
				scanf("%s", szTempName);
			
				for(int j = 0; j < nPetCount; j++)
					if(strcmp(szTempName, PetList[j].szPetName) == 0)
						nSameName = 1;
					
				if(nSameName)
					printf("There is already a pet with this name.\n");
			}while(nSameName);
			
			strcpy(PetList[index].szPetName, szTempName);
		}
		printf("Do you wish to edit its element? (1 - yes, 2 - no)\n");
		printf("> ");
		scanf("%d", &nChoice);
		scanf("%c", &cBuffer);
		if(nChoice == 1){
			printf("Current element: %s\n",PetList[index].szElement);
			printf("New element: ");
			scanf("%s", PetList[index].szElement);
		}
		
		printf("Do you wish to edit its description? (1 - yes, 2 - no)\n");
		printf("> ");
		scanf("%d", &nChoice);
		scanf("%c", &cBuffer);
		if(nChoice == 1){
			printf("Current description: %s\n",PetList[index].szDescription);
			printf("New description: ");
			scanf("%[^\n]", PetList[index].szDescription);
		}
		
		printf("Edit complete! Do you wish to edit more pokemon? (1 - yes, 2 - no)\n");
		printf("> ");
		scanf("%d", &nChoice);
	}while(nChoice == 1);
	
	fp = fopen("competdium.txt", "w");
	for(int i = 0; i < nPetCount && i < MAX_PETS; i++){
		fprintf(fp, "%s\n", PetList[i].szPetName);
		fprintf(fp, "%s\n", PetList[i].szElement);
		fprintf(fp, "%s\n", PetList[i].szDescription);
		fprintf(fp, "%d\n\n", PetList[i].nMatchCount);
	}
	
	fclose(fp);
}

void DeleteBattlePets(Grid PetList[], int *pPetCount){
	int nNum;
	int nChoice;
	
	FILE *fp = fopen("competdium.txt", "w");
	
	do{
		PrintBattlePets(PetList, *pPetCount);
		
		printf("Enter the number corresponding to the pokemon you wish to delete: ");
		scanf("%d", &nNum);
	
		for(int i = nNum - 1; i < *pPetCount && i < MAX_PETS; i++)
			PetList[i] = PetList[i + 1];
			
		(*pPetCount)--;
		
		if(*pPetCount > 0){
			printf("Do you wish to delete more pets? (1 - yes, 2 - no)\n");
			printf("> ");
			scanf("%d", &nChoice);
		}
		else
			printf("Looks like Competdium is empty now :-(.\n");
	}while(nChoice == 1 && *pPetCount > 0);
	
	for(int j = 0; j < *pPetCount && j < MAX_PETS; j++){
		fprintf(fp, "%s\n", PetList[j].szPetName);
		fprintf(fp, "%s\n", PetList[j].szElement);
		fprintf(fp, "%s\n", PetList[j].szDescription);
		fprintf(fp, "%d\n\n", PetList[j].nMatchCount);
	}
	
	fclose(fp);
}

void SaveRoster(Grid PetList[], int nPetCount){
	int nItemNum = 1;
	char szPetOfChoice[37];
	char playername[37];
	char filename[54] = "saved_roster.";
	Grid TempRoster[3][3];
	
	printf("Please input player name: ");
	scanf("%s", playername);
	strcat(filename, playername);
	strcat(filename, ".txt");
	
	printf("\n");
	
	for(int i = 0; i < 3; i++){
		for(int j = 0; j < 3; j++){
			int nIsSame;
			do{
				int nPetFound;
				do{//this do-while loop executes until the int variable nPetFound == 1 to make sure the user enters the pet name found in competdium
					nPetFound = 0;
					printf("%d > ", nItemNum);
					scanf("%s", szPetOfChoice);//accepts the name of the pet with the string variable szPetOfChoice
					for(int n = 0; n < nPetCount; n++)
						if(strcmp(PetList[n].szPetName, szPetOfChoice) == 0)
							nPetFound = 1;
							
					if(!nPetFound)//this if statement executes whenever nPetFound == 0 to tell the player the pet is not found in the competdium
						printf("Pet not found.\n");		
				}while(!nPetFound);
				
				nIsSame = 0;
				for(int o = 0; o < 3; o++)//this for loop checks if the inputted pet name in szPetOfName is the same as any of the pets in the current player's roster
					for(int p = 0; p < 3; p++)
						//this if statement executes whenever szPetOFChoice is the same as any of the pets in the current player's grid
						if(strcmp(TempRoster[o][p].szPetName, szPetOfChoice) == 0)
							nIsSame = 1;//the int variable nIsSame evaluates to 1 whenever szPetOfChoice is found to be the same as any pet in the current player's grid	
				//this if statement executes when nIsSame == 1, or when szPetOfChoice is found to be the same as any of the pets in the current player's grid	
				if(nIsSame)
					printf("This pet already exists in this roster.\n");
				//executetes when nIsSame != 1, or when szPetOfChoice is not found to be the same as any of the pets in the current player's grid, and then szPetOfChoice is put in the current player's gird
				else{
					strcpy(TempRoster[i][j].szPetName, szPetOfChoice);
					nItemNum++;
				} 	
			}while(nIsSame);
		}
	}
	
	FILE *fp = fopen(filename, "w");
	
	for(int k = 0; k < 3; k++)
		for(int l = 0; l < 3; l++)
			fprintf(fp, "%s\n", TempRoster[k][l].szPetName);
			
    fclose(fp);
}

