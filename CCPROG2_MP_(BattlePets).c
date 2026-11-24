/**
 * Description : This is a game simulation of BattlePets, where 2 players fight with their roster. 
  				 Either a player wins by the most number of wins, or whether they have a lucky win
				 (horizontal, vertical, diagonal)
 * Author/s : Pioc, Thomas Gabriel
 * 			  Buena, Jester Paul
 * Section : S20E
 * Last Modified : <25 November, 2026>
 * Acknowledgments : Gemini: used for assistance in answering questions about code concerns, Claude: used for assistance in answering questions about code concerns
 */


#include <stdio.h>
#include <string.h>
#include "BattlePetsFunctions.h"//header file containing the function definition of the functions in BattlePetsFunctions.c

int main(){
	FILE *fp;//opens the txt file competdium.txt to read all of its contents
	int nChoice;//int variable to store the choice of the player
	int nPetCount = 0, nPlayerCount = 0, i = 0;
	Grid PetList[MAX_PETS];//array of structs, with each struct containing relevant information of each pet
	PlayerInfo Player[PLAYERS];//array of structs, with each struct containing the username and roster of the player
	PlayerInfo PlayerList[MAX_PLAYERS];
	
	fp = fopen("competdium.txt", "r");
	
	//this while loop executes for as long as it can read the pet name found in competdium.txt into PetList
	while(fscanf(fp, "%s", PetList[nPetCount].szPetName) == 1 && i < MAX_PETS){
    	fscanf(fp, "%s", PetList[nPetCount].szElement); //reads the element of the pet
    	fgets(PetList[i].Buffer, sizeof(PetList[nPetCount].Buffer), fp); //gets the '\n' character found after the element
		fgets(PetList[i].szDescription, sizeof(PetList[nPetCount].szDescription), fp); //reads the description of the pet
		int length  = strlen(PetList[nPetCount].szDescription);
		PetList[nPetCount].szDescription[length - 1] = '\0';
		fscanf(fp, "%d", &PetList[nPetCount].nMatchCount); //reads the match count of the pet
		nPetCount++; //increments nPetCount (which represents the number of pets printed) every time all the information of a pet have been successfully read
    }
    
    fclose(fp);
    
	
	printf("WELCOME TO BATTLEPETS!\n");
	//this do-while loop executes for as long as nChoice != 0
	do{
    	if((fp = fopen("players.txt", "r")) != NULL){
    		while(fscanf(fp, "%s", PlayerList[nPlayerCount].szPlayerName) == 1 && nPlayerCount < MAX_PLAYERS){
	  			fscanf(fp, "%d", &PlayerList[nPlayerCount].nWin);
	  			fscanf(fp, "%d", &PlayerList[nPlayerCount].nLoss);
	  			fscanf(fp, "%d", &PlayerList[nPlayerCount].nDraw);
	  			nPlayerCount++;
			}
		}
		fclose(fp);
		
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
					BattleMenu(PetList, PlayerList, Player, &nPetCount, &nPlayerCount);
					break;
				case 2:
					PrintAddDeleteEditComp(PetList, &nPetCount);
					break;
				/*case 3:
					break;
					*/
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
