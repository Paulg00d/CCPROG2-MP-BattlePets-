/**
 * Description : This is a game simulation of BattlePets, where 2 players fight with their roster. 
  				 Either a player wins by the most number of wins, or whether they have a lucky win
				 (horizontal, vertical, diagonal)
 * Author/s : Pioc, Thomas Gabriel
 * 			 Buena, Jester Paul
 * Section : S20E
 * Last Modified : 15 November, 2026>
 * Acknowledgments : <list of references used in the making of this project>
 */


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

/**
 * This is to certify that this project is my/our own work, based on my/our personal
 * efforts in studying and applying the concepts learned. I/We have constructed the
 * functions and their respective algorithms and corresponding code by myself/ourselves.
 * The program was run, tested, and debugged by my/our own efforts. I/We further certify
 * that I/we have not copied in part or whole or otherwise plagiarized the work of
 * other students and/or persons.
 *
 * Pioc, Thomas Gabriel (DLSU ID# 12506559)
 * Buena, Jester Paul (DLSU ID# 12507164)
 */
