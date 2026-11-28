#include <stdio.h>
#include <string.h>
#include "CCPROG2_MP_(BattlePets)_Functions.h"

void StatisticsMenu(Grid PetList[], PlayerInfo PlayerList[], int nPetCount, int nPlayerCount){
	FILE *fp;
	
	SelectionSort(PetList, PlayerList, nPetCount, nPlayerCount);
	printf("Top 5 Players\n");
	if((fp = fopen("players.txt", "r")) == NULL){
		printf("There are no players recorded.\n");
		fclose(fp);
	}
	else{
		fclose(fp);
		for(int k = 0; k < 5 && strcmp(PlayerList[k].szPlayerName, "") != 0; k++){
		printf("%d. %s (W: %d, L: %d, D: %d)\n", k + 1, PlayerList[k].szPlayerName, PlayerList[k].nWin, PlayerList[k].nLoss, PlayerList[k].nDraw);
		}
	}
	
	
	printf("\n");
	
	printf("Top 5 BattlePets\n");
	for(int l = 0; l < 5 && strcmp(PetList[l].szPetName, "") != 0; l++)
		printf("%d. %s (%d matches)\n", l + 1, PetList[l].szPetName, PetList[l].nMatchCount);
}

void SelectionSort(Grid PetList[], PlayerInfo PlayerList[], int nPetCount, int nPlayerCount){
	Grid PetTemp;
	PlayerInfo PlayerTemp; 
	int max;
	
	for(int i = 0; i < nPetCount - 1; i++){
		max = i;
		for(int j = i + 1; j < nPetCount; j++){
			if(PetList[max].nMatchCount < PetList[j].nMatchCount)
				max = j;
		}
		if(i != max){
			PetTemp = PetList[i];
			PetList[i] = PetList[max];
			PetList[max] = PetTemp;
		}
	}
	
	for(int k = 0; k < nPlayerCount - 1; k++){
		max = k;
		for(int l = k + 1; l < nPlayerCount; l++){
			if(PlayerList[max].nWin < PlayerList[l].nWin)
				max = l;
		}
		if(k != max){
			PlayerTemp = PlayerList[k];
			PlayerList[k] = PlayerList[max];
			PlayerList[max] = PlayerTemp;
		}
	}
}
