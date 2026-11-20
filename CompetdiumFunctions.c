#include <stdio.h>
#include <string.h>
#include "BattlePetsFunctions.h"

void PrintAddDeleteEditComp(Grid PetList[], int nPetCount){
	int nChoice, i;
	
	printf("+------------------------------------+\n");
	printf("|  Choose what you want to do with   |\n");
	printf("|            the pets                |\n");
	printf("+-----------+------------------------+\n");
	printf("|     1     |    View BattlePets/s   |\n");
	printf("+-----------+------------------------+\n");
	printf("|     2     |      Add BattlePet     |\n");
	printf("+-----------+------------------------+\n");
	printf("|     2     |      Edit BattlePet    |\n");
	printf("+-----------+------------------------+\n");
	printf("|     2     |    Delete BattlePet    |\n");
	printf("+-----------+------------------------+\n");
	printf("> ");
	scanf("%d",&nChoice);
	
	switch(nChoice){
		case 1:
			for(i = 0; i < 60; i++){
				printf("%d.\n", i + 1);
				printf("Name: %s\n", Petlist[i].szPetname);
				printf("Element: %s\n", Petlist[i].szElement);
				printf("Description: %s", Petlist[i].szDescription);
				printf("Match count: %d\n\n", Petlist[i].nMatchCount);
			}
			
		case 2:
			

	}
}

