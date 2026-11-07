#include <stdio.h>
#include <string.h>
#include <BattlePetsFunctions.h>
#include <BattlePetsFunctions.c>

typedef struct {
	char szPetName[37];
	char szElement[9];
	char szDescription[114];
	int nMatchCount;
	char cSpace;
} PetList[60], Grid;

typedef struct {
	char szPlayerName[37];
	Grid PokeRoster[3][3];
}PlayerInfo[2];


int main(){
	FILE *fp;
	int nChoice;
	
	do {
		printf("WELCOME TO BATTLEPETS!\n");
		printf("+------------------------------------+\n");
		printf("|            Choose Here             |\n");
		printf("+-----------+------------------------+\n");
		printf("|     1     |         Battle!        |\n");
		printf("+-----------+------------------------+\n");
		printf("|     2     |       Competdium       |\n");
		printf("+-----------+------------------------+\n");
		printf("|     3     |     View Statistics    |\n");
		printf("+-----------+------------------------+\n");
		printf("|     0     |          Exit          |\n");
		printf("+-----------+------------------------+\n");
		printf("> ");
		scanf("%d", &nChoice);
		
		if (nChoice != 0){
			switch(nChoice){
				case 1:
					BattleMenu();
					break;
				case 2:
					break;
				case 3:
					break;
			}
		}
	
	}while(nChoice != 0);
	
	return 0;
}
