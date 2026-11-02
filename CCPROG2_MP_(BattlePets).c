#include <stdio.h>
#include <string.h>

typedef struct {
	char szPetName[37];
	char szElement[9];
	char szDescription[114];
} PetList[60];

typedef struct {
	char szPlayerName[37];
	Pokepet szPokeRoster[3][3];
}PlayerInfo;


int main(){
	PlayerInfo Player1, Player2;
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
					break;
				case 2:
					break;
				case 3:
					break;
			}
		}
				
	} while (nChoice != 0);
	
	return 0;
}
