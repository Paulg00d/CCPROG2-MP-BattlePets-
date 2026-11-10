#include <stdio.h>
#include <string.h>
#include <BattlePetsFunctions.h>
#include <BattlePetsFunctions.c>
#define MAX_PETS 60
#define PLAYER_COUNT 2


typedef struct {
	char szPetName[37];
	char szElement[9];
	char szDescription[114];
	int nMatchCount;
}Roster, Grid;

typedef struct {
	char szPlayerName[37];
	Roster PokeRoster[3][3];
}PlayerInfo;


int main(){
	FILE *fp;
	int nChoice;
	Grid PetList[MAX_PETS];
	PlayerInfo Player[PLAYER_COUNT];
	
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
					BattleMenu(&PetList, &Player);
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
