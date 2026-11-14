#include <stdio.h>
#include <string.h>
#include "BattlePetsFunctions.h"//header file containing the function definition of the functions in BattlePetsFunctions.c

int main(){
	FILE *fp;
	int nChoice;//int variable to store the choice of the player
	Grid PetList[MAX_PETS];//array of structs, with each struct containing relevant information of each pet
	PlayerInfo Player[MAX_PLAYERS];//array of structs, with each struct containing the username and roster of the player
	
	//this do-while loop executes for as long as nChoice != 0
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
		
		//this if statement executes whenevr nChoice != 0, or whenever the player chooses to exit
		if (nChoice != 0){
			switch(nChoice){
				case 1:
					BattleMenu(PetList, Player);
					break;
				case 2:
					break;
				case 3:
					break;
			}
		}
	
	}while(nChoice != 0);//this loop exits when the player chooses to exit
	
	return 0;
}
