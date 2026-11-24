#include <stdio.h>
#include <string.h>
#include "BattlePetsFunctions.h"

void PrintAddDeleteEditComp(Grid PetList[], int *pPetCount){
	FILE *fp;
	int nChoice, nChoice2;
	int nIsSame;
	//char szPetOfChoice[37];
	
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
	printf("> ");
	scanf("%d",&nChoice);
	
	switch(nChoice){
		case 1:
			PrintBattlePets(PetList, pPetCount);
			break;
			
		case 2:
			AddBattlePets(PetList, nPetCount, pPetCount)
			break;
		
		case 3:
			PrintBattlePets(PetList, pPetCount);
			EditBattlePets(PetList, pPetCount);
			break
			
		case 4:
			PrintBattlePets(PetList, pPetCount);
			DeleteBattlePets(PetList, pPetCount);
			break;
		case 5:
			PrintBattlePets(PetList, pPetCount);
			SaveRoster();
			break;
	}
}


void PrintBattlePets(Grid PetList[], int *pPetCount){
	for(int i = 0; i < *pPetCount && i < MAX_PETS; i++){
		printf("%d.\n", i + 1);
		printf("Name: %s\n", PetList[i].szPetName);
		printf("Element: %s\n", PetList[i].szElement);
		printf("Description: %s\n", PetList[i].szDescription);
		printf("Match count: %d\n\n", PetList[i].nMatchCount);
	}
}

void AddBattlePets(Grid PetList[], int *pPetCount){
	int nPetCount = *pPetCount;
	int nRemainingPets = MAX_PETS - *pPetCount;
	int nChoice;
	char cBuffer;
	
	printf("%d more pets can be added to Competdium.\n", nRemainingCount);
	
	do{
		printf("|---There are now %d pets in Competdium.---|\n", *pPetCount);
		printf("Enter the name: ");
		scanf("%s", PetList[*pPetCount].szPetName);
		scanf("%c", &cBuffer);
		printf("Enter the element: ");
		scanf("%s", PetList[*pPetCount].szElement);
		scanf("%c", &cBuffer);
		printf("Enter the description: ");
		scanf("%s", PetList[*pPetCount].szDescription);
		PetList[*pPetCount].nMatchCount = 0;
		
		(*pPetCount)++;
		nRemainingPets--;
		
		printf("Would you like to enter another pet? (1 - yes, 2 - no)\n");
		printf("> ");
		scanf("%d", &nChoice);
	}while(nChoice == 1 && nRemainingPets > 0);
}

void EditBattlePets(Grid PetList[], int *pPetCount){
	FILE *fp;
	int nChoice;
	int index;
	
	do{
		printf("Please input the number for the pokemon you wish to edit:");
		scanf("%d", &index);
		index--;
		
		printf("|---Editing %s---|\n", PetList[index].szPetName);
		printf("Do you wish to edit its name? (1 - yes, 2 - no)\n");
		printf("> ");
		scanf("%d", nChoice);
		if(nChoice == 1){
			printf("Current name: %s\n",PetList[index].szPetName);
			printf("New name: ");
			scanf("%s", PetList[index].szPetname);
		}
		
		printf("Do you wish to edit its element? (1 - yes, 2 - no)\n");
		printf("> ");
		scanf("%d", nChoice);
		if(nChoice == 1){
			printf("Current element: %s\n",PetList[index].szElement);
			printf("New element: ");
			scanf("%s", PetList[index].szElement);
		}
		
		printf("Do you wish to edit its description? (1 - yes, 2 - no)\n");
		printf("> ");
		scanf("%d", nChoice);
		if(nChoice == 1){
			printf("Current description: %s\n",PetList[index].szPetName);
			printf("New description: ");
			scanf("%[\n]", PetList[index].szDescription);
		}
		
		printf("Edit complete! Do you wish to edit more pokemon? (1 - yes, 2 - no)\n");
		printf("> ");
		scanf("%d", &nChoice);
	}while(nChoice == 1);
	
	fp = fopen("competdium.txt", "w");
	for(int i = 0; i < *pPetCount && i , MAX_PETS; i++){
		fprintf("%s\n", PetList[i].szPetName);
		fprintf("%s\n", PetList[i].szElement);
		fprintf("%s\n", PetList[i].szDescription);
		fprintf("%d\n\n", PetList[i].nMatchCount);
	}
	
	fclose(fp);
}

void DeleteBattlePets(Grid PetList[], int *pPetCount){
	int nNum;
	int nPetCount = *pPetCount;
	int nChoice;
	
	FILE *fp = fopen("competdium.txt", "w");
	
	do{
		printf("Enter the number for the pokemon you wish to delete: ");
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
			printf("Looks like Competdium is empty now :-(.\n")
	}while(nChoice == 1 && *pPetcount > 0);
	
	for(int j = 0; j < *pPetCount && j < MAX_PETS; j++){
		fprintf(fp, "%s\n", PetList[j].szPetName);
		fprintf(fp, "%s\n", PetList[j].szElement);
		fprintf(fp, "%s\n", PetList[j].szDescription);
		fprintf(fp, "%d\n\n", PetList[j].nMatchCount);
	}
	
	fclose(fp);
}



void SaveRoster(){
	char playername[37];
	char filename[54] = "saved_roster.";
	Grid TempRoster[3][3];
	
	printf("Please input player name: ");
	scanf("%s",playername);
	strcat(filename, playername);
	strcat(filename, ".txt");
	
	for(int i = 0; i < 3; i++){
		for(int j = 0; j < 3; j++){
			printf("\n\nPlease input pokemon: ");
			scanf("%s", TempRoster[i][j].szPetName);
		}
	}
	
	FILE *fp = fopen(filename, "w");
	
	for(int k = 0; k < 3; k++)
		for(int l = 0; l < 3; l++)
			fprintf(fp, "%s\n", TempRoster[k][l].szPetName);
			
    fclose(fp);
}

