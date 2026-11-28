#include <stdio.h>
#include <string.h>
#include "CCPROG2_MP_(BattlePets)_Functions.h"

/**
 * The function BattleMenu is called when the player chooses the first option (Battle!) in the main menu
 * @param PetList is an array of structs, with each struct containing the information of each battle pet (name, element, description, match count)
 * @param PlayerList is an array of structs, with each struct containing the information of each player (name, number of wins, number of losses, number of draws)
 * @param Player is an array of structs, with each struct containing the information of the players currently playing (name, roster), of which there are two
 * @param *pPetCount is an int pointer representing the current number of pets in PetList and the Competdium
 * @param nPlayerCount is an int variable contining the current number of players who have played, stored in PlayerList
 * @pre nPlayerCount starts at 0
 */
void BattleMenu(Grid PetList[], PlayerInfo PlayerList[], PlayerInfo Player[], int nPetCount, int nPlayerCount){
	int nChoice;/*this variable stores the choice of the player in choosing a new or existing username*/
  	int nChoice2;/*this variable stores whether the player wants to load a saved roster or create a new roster*/
  	char szPetOfChoice[37];/*this string variable stores the pet name entered by the player*/
  	FILE *fp;

  	//this for loop iterates between player 1 and player 2
  	for(int nCurrentPlayer = 0; nCurrentPlayer < PLAYERS; nCurrentPlayer++){
  	  	printf("+------------------------------------+\n");
	  	printf("|             Player %d               |\n", nCurrentPlayer + 1);
	  	printf("+-----------+------------------------+\n");
	  	printf("|     1     |      <New Player>      |\n");
	  	printf("+-----------+------------------------+\n");
	  	//this if statement executes if players.txt already exists (it is created after th very first match conducted in this game)
	  	if((fp = fopen("players.txt", "r")) != NULL){
	  		fclose(fp);//closes the file immediately as players.txt would have already been opened in the previous function
	  		for(int i = 0; i < nPlayerCount; i++){//this for loop prints all the player usernames used in previous matches
			  	printf("|     %d     |      %s      |\n", i + 2, PlayerList[i].szPlayerName);
		  		printf("+-----------+------------------------+\n");
		  	}
		  }
	  
		  printf("> ");
		  scanf("%d", &nChoice);
		  //when option 1 is chosen (choosing a new username)
	      if(nChoice == 1){
			printf("Enter username: ");
			scanf("%s", Player[nCurrentPlayer].szPlayerName);
		  }
		  //when the player chooses to use an existing username
		  else{
		  	strcpy(Player[nCurrentPlayer].szPlayerName, PlayerList[nChoice - 2].szPlayerName);
		  } 
			printf("+------------------------------------+\n");
		  	printf("|  Time to choose your battle pets!  |\n");
		  	printf("+-----------+------------------------+\n");
		  	printf("|     1     |    Load saved roster   |\n");
		  	printf("+-----------+------------------------+\n");
		  	printf("|     2     |    Create roster for   |\n");
		  	printf("|           |       this match       |\n");
		  	printf("+-----------+------------------------+\n");
			printf("> ");
			scanf("%d", &nChoice2);
		
			switch(nChoice2){
				//chosen when the player chooses to load their saved roster savedroster/<player_name>.txt.
				case 1: LoadRoster(PetList, Player, nPetCount, nCurrentPlayer); //loads the contents of savedroster/<player_name>.txt onto the roster of the current player (the player indicated by the nCurrentPlayer index)
						break;
						
				//chosen when the player chooses to create their own roster for the game
				case 2: printf("+------------------------------------+\n");
  						printf("|            Competdium              |\n");
		  				printf("+------------------------------------+\n");
						PrintBattlePets(PetList, nPetCount);
						int nItemNum = 1;
						//this for loop iterates each cell of the current player's grid
						for(int l = 0; l < 3; l++){//iterates between rows
							for(int m = 0; m < 3; m++){//iterates between columns
								//this do-while loop executes until the int variable nIsSame == 0 to make sure the entered pet name is not the same as any pet in the current player's grid
								int nIsSame;
								do{
									nIsSame = 0;
									printf("%d > ", nItemNum);
									scanf("%s", szPetOfChoice);//accepts the name of the pet with the string variable szPetOfChoice
									int nPetFound = 0;
									//this while loop executes until the int variable nPetFound == 1 to make sure the user enters the pet name found in competdium
									while(nPetFound != 1){
										for(int n = 0; n < nPetCount; n++)
											if(strcmp(PetList[n].szPetName, szPetOfChoice) == 0)
												nPetFound = 1;
										if(nPetFound == 0){//this if statement executes whenever nPetFound == 0 to tell the player the pet is not found in the competdium
											printf("Pet not found.\n");
											printf("> ");
											scanf("%s", szPetOfChoice);//accepts the name of the pet with the string variable szPetOfChoice
										}
									}							
									//this for loop checks if the inputted pet name in szPetOfName is the same as any of the pets in the current player's roster
									for(int o = 0; o < 3; o++){
										for(int p = 0; p < 3; p++){							
											//this if statement executes whenever szPetOFChoice is the same as any of the pets in the current player's grid
											if(strcmp(Player[nCurrentPlayer].PokeRoster[o][p].szPetName, szPetOfChoice) == 0)
												nIsSame = 1;//the int variable nIsSame evaluates to 1 whenever szPetOfChoice is found to be the same as any pet in the current player's grid
										}								
									}
											
									//this if statement executes when nIsSame == 1, or when szPetOfChoice is found to be the same as any of the pets in the current player's grid	
									if(nIsSame)
										printf("This pet already exists in your roster.\n");
										
									//executetes when nIsSame != 1, or when szPetOfChoice is not found to be the same as any of the pets in the current player's grid, and then szPetOfChoice is put in the current player's gird
									else{ 	
										strcpy(Player[nCurrentPlayer].PokeRoster[l][m].szPetName, szPetOfChoice);
										nItemNum++;
										for(int q = 0; q < nPetCount; q++){
											if(strcmp(Player[nCurrentPlayer].PokeRoster[l][m].szPetName, PetList[q].szPetName) == 0){
												strcpy(Player[nCurrentPlayer].PokeRoster[l][m].szElement, PetList[q].szElement);
												strcpy(Player[nCurrentPlayer].PokeRoster[l][m].szDescription, PetList[q].szDescription);
												Player[nCurrentPlayer].PokeRoster[l][m].nMatchCount = PetList[q].nMatchCount;
											}
										}
											
									}
								}while(nIsSame);//this do-while loop exits when nIsSame == 0
							}
						}
				  	  	break;		
			}	
	  	}
  	
	  	//this function is called to have the rosters of the 2 players fight and to store the result of each battle grid cell in an int array
	  	Battle(PetList, nPetCount, Player, PlayerList, Player[0].PokeRoster, Player[1].PokeRoster, Player[0].szPlayerName, Player[1].szPlayerName, nPlayerCount);
	
		//this for loop and nested for loops clear the name, element, and description of each pet in the players' rosters once the match is over
		for(int r = 0; r < PLAYERS; r++){
			for(int s = 0; s < 3; s++){
				for(int t = 0; t < 3; t++){
					Player[r].PokeRoster[s][t].szPetName[0] = '\0';
					Player[r].PokeRoster[s][t].szElement[0] = '\0';
					Player[r].PokeRoster[s][t].szDescription[0] = '\0';
				}
			}
		}	
}

void SaveMatchResults(PlayerInfo Player[], int BattleGrid[][3]){
	FILE *fp;
	char filename[22] = "results.match_";
	char cNum = '1';
	
	filename[14] = cNum;
	strcat(filename, ".txt");
	
	while((fp = fopen(filename, "r")) != NULL){
		fclose(fp);
		int length = strlen(filename);
		for(int i = length - 1; filename[i] != '_'; i--)
			filename[i] = '\0';
		cNum += 1;
		filename[14] = cNum;
		strcat(filename, ".txt");
	}
	
	fclose(fp);
	
	fp = fopen(filename, "w");
	
	for(int i = 0; i < PLAYERS; i++)
		fprintf(fp, "Player%d: %s\n", i + 1, Player[i].szPlayerName);
		
	fprintf(fp, "\n");
	fprintf(fp, "P1 Roster vs. P2 Roster\n");
	for(int j = 0; j < 3; j++)
		for(int k = 0; k < 3; k++)
			fprintf(fp, "%s vs. %s\n", Player[0].PokeRoster[j][k].szPetName, Player[1].PokeRoster[j][k].szPetName);
	
	fprintf(fp, "\n");
	fprintf(fp, "Match Results\n");
	
	for(int l = 0; l < 3; l++){
		for(int m = 0; m < 3; m++){
			if(m == 2){
				if(BattleGrid[l][m] == 0)
					fprintf(fp, "D\n");
				else
					fprintf(fp, "%d\n", BattleGrid[l][m]);
			}
			else{
				if(BattleGrid[l][m] == 0)
					fprintf(fp, "D ");
				else
					fprintf(fp, "%d ", BattleGrid[l][m]);
			}
		}
	}
	
	fprintf(fp, "\nWinner: ");
	
	int nHasWinner = 0;
	for(int n = 0; n < PLAYERS; n++){
		if(Player[n].nWin == 1){
			fprintf(fp, "%s\n", Player[n].szPlayerName);
			switch(Player[n].cWinType){
				case 'M':
					fprintf(fp, "Type of Win: Majority Win\n");
					break;
				case 'L':
					fprintf(fp, "Type of Win: Lucky Win\n");
					break;
			}
		}
	}
	
	fclose(fp);
			
}

/**
 * The function UpdateCompetdium updates the match count of the pets found in Competdium if they have been used in battle 
 * @param Player[] is an array of structs, with each struct containing the information of each player (name, wins, losses, draws, roster), of which there are two
 * @param PetList[] is a list of structs, with each struct containing the information of each battle pet (name, element, description, match count)
 * @pre PetList already contains the information from Competdium, Player already contains information of the two players playing the game, and *pPetCount is a non-negative integer
 */
void UpdateCompetdium(PlayerInfo Player[], Grid PetList[], int nPetCount){
	FILE *fp;
	
	for(int i = 0; i < 3; i++)
		for(int j = 0; j < 3; j++)
			for(int k = 0; k < nPetCount; k++)
				if(strcmp(Player[0].PokeRoster[i][j].szPetName, PetList[k].szPetName) == 0)
					PetList[k].nMatchCount += Player[0].PokeRoster[i][j].nMatchCount;
					
	for(int l = 0; l < 3; l++){
		for(int m = 0; m < 3; m++){
			int nIsSame = 0;
			
			for(int n = 0; n < 3; n++){
				for(int o = 0; o < 3; o++){
					if(strcmp(Player[1].PokeRoster[l][m].szPetName, Player[0].PokeRoster[n][o].szPetName) == 0){
						nIsSame = 1;
					}
				}
			}
			
			if(!nIsSame){
				for(int p = 0; p < nPetCount; p++){
					if(strcmp(Player[1].PokeRoster[l][m].szPetName, PetList[p].szPetName) == 0){
						PetList[p].nMatchCount += Player[1].PokeRoster[l][m].nMatchCount;
					}
				}
			}
		}
	}
	
	fp = fopen("competdium.txt", "w");
	
	for(int q = 0; q < nPetCount; q++){
		fprintf(fp, "%s\n", PetList[q].szPetName);
		fprintf(fp, "%s\n", PetList[q].szElement);
		fprintf(fp, "%s\n", PetList[q].szDescription);
		fprintf(fp, "%d\n\n", PetList[q].nMatchCount);
	}
		
	fclose(fp);		
			
}


/**
 * The function SavePlayerResults saves the name, wins, losses, and draw of each of the players who participated in the battle in a file called players.txt, whereas it also saves the result of the match in 
 * @param Player[] is an array of structs, with each struct containing the information of each player (name, wins, losses, draws, roster), of which there are two
 * @param PlayerList[] is a list of structs, with each struct containing the information of each battle pet (name, element, description, match count)
 * @param nPlayerCount is a int variable containing the current number of players in PlayerList[]
 * @pre PlayerList contains the usernames of all players that have played in the game before and nPlayerCount is at least 0
 */
void SavePlayerResults(PlayerInfo Player[], PlayerInfo PlayerList[], int nPlayerCount){
	FILE *fp;
	int nFound;
	
	for(int i = 0; i < PLAYERS; i++){
		nFound = 0;
		for(int j = 0; j < MAX_PLAYERS; j++){
			if(strcmp(Player[i].szPlayerName, PlayerList[j].szPlayerName) == 0){
				nFound = 1;
				PlayerList[j].nWin += Player[i].nWin;
				PlayerList[j].nLoss += Player[i].nLoss;
				PlayerList[j].nDraw += Player[i].nDraw;
			}
		}
		
		if(!nFound){
			strcpy(PlayerList[nPlayerCount].szPlayerName, Player[i].szPlayerName);
			PlayerList[nPlayerCount].nWin = Player[i].nWin;
			PlayerList[nPlayerCount].nLoss = Player[i].nLoss;
			PlayerList[nPlayerCount].nDraw = Player[i].nDraw;
			nPlayerCount++;
		}
	}
	
	fp = fopen("players.txt", "w");
	
	for(int k = 0; k < nPlayerCount; k++){
		fprintf(fp, "%s\n", PlayerList[k].szPlayerName);
		fprintf(fp, "%d\n", PlayerList[k].nWin);
		fprintf(fp, "%d\n", PlayerList[k].nLoss);
		fprintf(fp, "%d\n\n", PlayerList[k].nDraw);
	}
	
	fclose(fp);
}


/**
 * The function LoadRoster loads the contents of savedroster/<player_name>.txt onto the roster of the current player (the player indicated by the nCurrentPlayer index)
 * @param PetList[] is an list of structs, with each struct containing the information of each battle pet (name, element, description, match count)
 * @param Player is an array of structs, with each struct containing the information of each player (name, roster), of which there are two
 * @param *pPetCount is an int pointer pointing to the an int variable containing the number of pets stored in PetList so far (maximum is 60)
 * @param nCurrentPlayer is the index of the Player[] array of structs indicating the current player
 * @pre *pPetCount and nCurrentPlayer both start at 0
 */
void LoadRoster(Grid PetList[], PlayerInfo Player[], int nPetCount, int nCurrentPlayer){
	char szFileName[35] = "saved_roster."; //string to stor the name of the txt file containing the saved roster
	char szTemp[35];
	
	printf("Please write here the name of the file.\n");
	printf("Note: Please do not include .txt after writing its name because .txt will already be included in the file name by the system.\n");
	printf("(For example: if you type cars.txt, then the system will try to search for saved_roster.cars.txt.txt)\n");
	printf("> ");
    scanf("%s", szTemp);
    
    strcat(szFileName, szTemp); //catenates the username entered in szTemp to szFileName which already contains the string "saved_roster."
    strcat(szFileName, ".txt"); //catenates the string ".txt" to the end of the string contained in the string variable bar

	
	FILE *fp = fopen(szFileName,"r"); //opens the txt file bearing the same name as bar to read its contents
    
    //this for loop goes to each cell of the current player's grid
    for(int j = 0; j < 3; j++)
    	for(int k = 0; k < 3; k++)
    		fscanf(fp,"%s", Player[nCurrentPlayer].PokeRoster[j][k].szPetName); //puts the pet names of the txt file with the same name as bar into each cell of the current player's grid
    
    int nIsSame;//flag to check if any of the pets in the player's saved roster is found in competdium. For each cell in the player's grid, it evaluates to 1 if it is found in competdium, and 0 if otherwise
    
    //this for loop goes to each cell of the player's roster grid to check if the pet in the current cell is found in competdium or not
    for(int l = 0; l < 3; l++){
    	for(int m = 0; m < 3; m++){
    		nIsSame = 0;
        	for(int n = 0; n < nPetCount; n++){
        		if(strcmp(Player[nCurrentPlayer].PokeRoster[l][m].szPetName, PetList[n].szPetName) == 0){
        			strcpy(Player[nCurrentPlayer].PokeRoster[l][m].szElement, PetList[n].szElement);
        			fgets(Player[nCurrentPlayer].PokeRoster[l][m].Buffer, sizeof(Player[nCurrentPlayer].PokeRoster[l][m].Buffer), fp);
        			fgets(Player[nCurrentPlayer].PokeRoster[l][m].szDescription, sizeof(Player[nCurrentPlayer].PokeRoster[l][m].szDescription), fp);
        			nIsSame = 1;
				}
			}
			if(nIsSame == 0){
				printf("Ohhhh we got a newcomer here! Time to give %s an element!\n", Player[nCurrentPlayer].PokeRoster[l][m].szPetName);
				printf("> ");
				scanf("%s", Player[nCurrentPlayer].PokeRoster[l][m].szElement);
			}
		}
	}
	
	fclose(fp);
}



/**
 * The function Battle stores the result of the fight between the rosters of the two players. Whichever pet wins, loses, or neither in each grid cell is stored in a new grid
 * @param Petlist is an array of structs with each struct containing the information of all pets in Competdium (name, element, description, match count)
 * @param *pPetCount is an int pointer variable containing the current number of pets in Competdium
 * @param Player is an array of structs containing the information of the currently playing players (name, number of wins, number of losses, number of draws, roster)
 * @param PlayerList is an array of structs containing the usernames of all players who have played the game before
 * @param Player1Roster is the roster of Player 1 in the form of a 2d array of structs, where each struct stores the name and element of each player
 * @param Player2Roster is the roster of Player 2 in the form of a 2d array of structs, where each struct stores the name and element of each player
 * @param Player1name is the username of player 1
 * @param Player2name is the username of player 2
 * @param nPlayerCount is an int variable containing the current count of players stored in PlayerList
 * @pre Player1Roster and Player2Roster already have the relevant pet information each, and Player1Name and Player2Name already contain the names of the players, nPlayerCount is at least 0
 */
void Battle(Grid PetList[], int nPetCount, PlayerInfo Player[], PlayerInfo PlayerList[], Roster Player1Roster[][3], Roster Player2Roster[][3], char *Player1name, char *Player2name, int nPlayerCount){
	int BattleGrid[3][3];//an int array to display if one player won or if it is a tie in each cell (1 - player 1 wins, 2 - player 2 wins, 0 - it is a draw)
	int Player1;/*an int variable to contain how many lucky wins player 1 has (e.g. 2 horizontal wins, 2 vertical wins)*/
	int Player2;/*an int variable to contain how many lucky wins player 2 has (e.g. 2 horizontal wins, 2 vertical wins)*/
	int i, g;//int variables to go to each cell in each of the two player rosters and in BattleGrid[][]
	int count1 = 0, count2 = 0;//Basically counts how many 1's or 2's are there
	
	printf("%s (Player 1) vs. %s (Player 2)\n\n", Player1name, Player2name);
	printf("BattlePets, Fight!\n");
	for(int p = 0; p < 3; p++)
		for(int q = 0; q < 3; q++)
			printf("[%d][%d] - %s vs %s\n", p, q, Player1Roster[p][q].szPetName, Player2Roster[p][q].szPetName);
	printf("\n");
	
	//this for loop goes to each cell in player 1 and player 2's rosters and BattleGrid to assign a value to show who wins or if it is a draw
    for(i = 0; i < 3; i++){
        for(g = 0; g < 3; g++){
        	//if statement to check if the element of player 1 in [i][g] is fire
    		if(strcmp(Player1Roster[i][g].szElement, "Fire") == 0){
       			if(strcmp(Player2Roster[i][g].szElement, "Grass") == 0 || strcmp(Player2Roster[i][g].szElement, "Earth") == 0 || strcmp(Player2Roster[i][g].szElement, "Ice") == 0)
       				BattleGrid[i][g] = 1;//evaluates to 1 if player 1 wins against player 2 in cell [i][g]
       			else if(strcmp(Player2Roster[i][g].szElement, "Water") == 0 || strcmp(Player2Roster[i][g].szElement, "Metal") == 0)
       				BattleGrid[i][g] = 2;//evaluates to 2 if player 2 wins against player 1 in cell [i][g]
    			else if(strcmp(Player2Roster[i][g].szElement, "Fire") == 0 || strcmp(Player2Roster[i][g].szElement, "Air") == 0 || strcmp(Player2Roster[i][g].szElement, "Electric") == 0)
       				BattleGrid[i][g] = 0;//evaluates to 0 if neither player 1 nor player 2 can win over the other
			}
       		//if statement to check if the element of player 1 in [i][g] is water
            else if(strcmp(Player1Roster[i][g].szElement, "Water") == 0){
    			if(strcmp(Player2Roster[i][g].szElement, "Fire") == 0 || strcmp(Player2Roster[i][g].szElement, "Electric") == 0 || strcmp(Player2Roster[i][g].szElement, "Metal") == 0)
       				BattleGrid[i][g] = 1;//evaluates to 1 if player 1 wins against player 2 in cell [i][g]
       			else if(strcmp(Player2Roster[i][g].szElement, "Grass") == 0 || strcmp(Player2Roster[i][g].szElement, "Ice") == 0)
       				BattleGrid[i][g] = 2;//evaluates to 2 if player 2 wins against player 1 in cell [i][g]
       			else if(strcmp(Player2Roster[i][g].szElement, "Water") == 0 || strcmp(Player2Roster[i][g].szElement, "Earth") == 0 || strcmp(Player2Roster[i][g].szElement, "Air") == 0)
       				BattleGrid[i][g] = 0;//evaluates to 0 if neither player 1 nor player 2 can win over the other
			}
       		//if statement to check if the element of player 1 in [i][g] is grass
			else if(strcmp(Player1Roster[i][g].szElement, "Grass") == 0){
       			if(strcmp(Player2Roster[i][g].szElement, "Water") == 0 || strcmp(Player2Roster[i][g].szElement, "Earth") == 0 || strcmp(Player2Roster[i][g].szElement, "Electric") == 0)
       				BattleGrid[i][g] = 1;//evaluates to 1 if player 1 wins against player 2 in cell [i][g]
    			else if(strcmp(Player2Roster[i][g].szElement, "Fire") == 0 || strcmp(Player2Roster[i][g].szElement, "Air") == 0 || strcmp(Player2Roster[i][g].szElement, "Ice") == 0)
       				BattleGrid[i][g] = 2;//evaluates to 2 if player 2 wins against player 1 in cell [i][g]
       			else if(strcmp(Player2Roster[i][g].szElement, "Grass") == 0 || strcmp(Player2Roster[i][g].szElement, "Metal") == 0)
       				BattleGrid[i][g] = 0;//evaluates to 0 if neither player 1 nor player 2 can win over the other
			}
			//if statement to check if the element of player 1 in [i][g] is earth
			else if(strcmp(Player1Roster[i][g].szElement, "Earth") == 0){
       			if(strcmp(Player2Roster[i][g].szElement, "Air") == 0 || strcmp(Player2Roster[i][g].szElement, "Metal") == 0)
       				BattleGrid[i][g] = 1;//evaluates to 1 if player 1 wins against player 2 in cell [i][g]
    			else if(strcmp(Player2Roster[i][g].szElement, "Fire") == 0 || strcmp(Player2Roster[i][g].szElement, "Grass") == 0 || strcmp(Player2Roster[i][g].szElement, "Electric") == 0)
       				BattleGrid[i][g] = 2;//evaluates to 2 if player 2 wins against player 1 in cell [i][g]
       			else if(strcmp(Player2Roster[i][g].szElement, "Earth") == 0 || strcmp(Player2Roster[i][g].szElement, "Water") == 0 || strcmp(Player2Roster[i][g].szElement, "Ice") == 0)
       				BattleGrid[i][g] = 0;//evaluates to 0 if neither player 1 nor player 2 can win over the other
			}
			//if statement to check if the element of player 1 in [i][g] is air
			else if(strcmp(Player1Roster[i][g].szElement, "Air") == 0){
       			if(strcmp(Player2Roster[i][g].szElement, "Grass") == 0 || strcmp(Player2Roster[i][g].szElement, "Electric") == 0)
       				BattleGrid[i][g] = 1;//evaluates to 1 if player 1 wins against player 2 in cell [i][g]
    			else if(strcmp(Player2Roster[i][g].szElement, "Earth") == 0 || strcmp(Player2Roster[i][g].szElement, "Ice") == 0 || strcmp(Player2Roster[i][g].szElement, "Metal") == 0)
       				BattleGrid[i][g] = 2;//evaluates to 2 if player 2 wins against player 1 in cell [i][g]
       			else if(strcmp(Player2Roster[i][g].szElement, "Air") == 0 || strcmp(Player2Roster[i][g].szElement, "Fire") == 0 || strcmp(Player2Roster[i][g].szElement, "Water") == 0)
       				BattleGrid[i][g] = 0;//evaluates to 0 if neither player 1 nor player 2 can win over the other
			}
			//if statement to check if the element of player 1 in [i][g] is electric
			else if(strcmp(Player1Roster[i][g].szElement, "Electric") == 0){
       			if(strcmp(Player2Roster[i][g].szElement, "Earth") == 0 || strcmp(Player2Roster[i][g].szElement, "Metal") == 0)
       				BattleGrid[i][g] = 1;//evaluates to 1 if player 1 wins against player 2 in cell [i][g]
    			else if(strcmp(Player2Roster[i][g].szElement, "Water") == 0 || strcmp(Player2Roster[i][g].szElement, "Grass") == 0 || strcmp(Player2Roster[i][g].szElement, "Air") == 0 || strcmp(Player2Roster[i][g].szElement, "Ice") == 0)
       				BattleGrid[i][g] = 2;//evaluates to 2 if player 2 wins against player 1 in cell [i][g]
       			else if(strcmp(Player2Roster[i][g].szElement, "Electric") == 0 || strcmp(Player2Roster[i][g].szElement, "Fire") == 0)
       				BattleGrid[i][g] = 0;//evaluates to 0 if neither player 1 nor player 2 can win over the other
			}
			//if statement to check if the element of player 1 in [i][g] is electric
			else if(strcmp(Player1Roster[i][g].szElement, "Ice") == 0){
       			if(strcmp(Player2Roster[i][g].szElement, "Water") == 0 || strcmp(Player2Roster[i][g].szElement, "Grass") == 0 || strcmp(Player2Roster[i][g].szElement, "Air") == 0 || strcmp(Player2Roster[i][g].szElement, "Electric") == 0)
       				BattleGrid[i][g] = 1;//evaluates to 1 if player 1 wins against player 2 in cell [i][g]
    			else if(strcmp(Player2Roster[i][g].szElement, "Fire") == 0 || strcmp(Player2Roster[i][g].szElement, "Metal") == 0)
       				BattleGrid[i][g] = 2;//evaluates to 2 if player 2 wins against player 1 in cell [i][g]
       			else if(strcmp(Player2Roster[i][g].szElement, "Ice") == 0 || strcmp(Player2Roster[i][g].szElement, "Earth") == 0)
       				BattleGrid[i][g] = 0;//evaluates to 0 if neither player 1 nor player 2 can win over the other
			}
			//if statement to check if the element of player 1 in [i][g] is electric
			else if(strcmp(Player1Roster[i][g].szElement, "Metal") == 0){
       			if(strcmp(Player2Roster[i][g].szElement, "Fire") == 0 || strcmp(Player2Roster[i][g].szElement, "Air") == 0 || strcmp(Player2Roster[i][g].szElement, "Ice") == 0)
       				BattleGrid[i][g] = 1;//evaluates to 1 if player 1 wins against player 2 in cell [i][g]
    			else if(strcmp(Player2Roster[i][g].szElement, "Water") == 0 || strcmp(Player2Roster[i][g].szElement, "Earth") == 0 || strcmp(Player2Roster[i][g].szElement, "Electric") == 0)
       				BattleGrid[i][g] = 2;//evaluates to 2 if player 2 wins against player 1 in cell [i][g]
       			else if(strcmp(Player2Roster[i][g].szElement, "Metal") == 0 || strcmp(Player2Roster[i][g].szElement, "Grass") == 0)
       				BattleGrid[i][g] = 0;//evaluates to 0 if neither player 1 nor player 2 can win over the other
			}
        }
    }
    
    printf("Match Results:\n");
    printf("+---+---+---+\n");
    for(int i = 0; i < 3; i++){
    	printf("|");
    	for(int j = 0; j < 3; j++){
    		if(j == 2){
    			if(BattleGrid[i][j] == 0)
    				printf(" D |\n");
    			else
    				printf(" %d |\n", BattleGrid[i][j]);
					
				printf("+---+---+---+\n");
			}
			else{
				if(BattleGrid[i][j] == 0)
    				printf(" D |");
    			else
    				printf(" %d |", BattleGrid[i][j]);
			}
		}
	}
	printf("\n");
    	

	Player1 = Horizontal(BattleGrid, 1) + Vertical(BattleGrid, 1) + Diagonal(BattleGrid, 1);//Player1 calls the functions show to store how many lucky wins player 1 has
	Player2 = Horizontal(BattleGrid, 2) + Vertical(BattleGrid, 2) + Diagonal(BattleGrid, 2);//Player2 calls the functions show to store how many lucky wins player 2 has


	if(Player1 > Player2){//executes if player 1 has more lucky wins than player 2
		printf("Winner: %s (Player 1) [Lucky Win]\n\n", Player1name);
		Player[0].cWinType = 'L';
		Player[0].nWin = 1;
		Player[0].nLoss = 0;
		Player[0].nDraw = 0;
		Player[1].nWin = 0;
		Player[1].nLoss = 1;
		Player[1].nDraw = 0;
	}
    else if(Player2 > Player1){//executes if player 2 has more lucky wins than player 1
		printf("Winner: %s (Player 2) [Lucky Win]\n\n", Player2name);
		Player[1].cWinType = 'L';
		Player[0].nWin = 0;
		Player[0].nLoss = 1;
		Player[0].nDraw = 0;
		Player[1].nWin = 1;
		Player[1].nLoss = 0;
		Player[1].nDraw = 0;
	}
	//executes if neither player has any lucky wins or if both have the same number of lucky wins (e.g. both player 1 and player 2 have 1 horizontal win each)
	else{
	//this for loop goes to each cell of BattleGrid to count how many 1's and/or 2's there are
		for(i=0;i<3;i++){
			for(g=0;g<3;g++){
				if(BattleGrid[i][g]==1){
					count1+=1;//increments whenever 1 is in the cell [i][g]
				}
				else if(BattleGrid[i][g]==2){
					count2+=1;//increments whenever 2 is in the cell [i][g]
				}
			}
		}
		if(count1 > count2){//executes if player 1 has more wins than player 2
			printf("Winner: %s (Player 1) [Majority Win]\n\n", Player1name);
			Player[0].cWinType = 'M';
			Player[0].nWin = 1;
			Player[0].nLoss = 0;
			Player[0].nDraw = 0;
			Player[1].nWin = 0;
			Player[1].nLoss = 1;
			Player[1].nDraw = 0;
		}
		else if(count2 > count1){//executes if player 2 has more wins than player 1
			printf("Winner: %s (Player 2) [Majority Win]\n\n", Player2name);
			Player[1].cWinType = 'M';
			Player[0].nWin = 0;
			Player[0].nLoss = 1;
			Player[0].nDraw = 0;
			Player[1].nWin = 1;
			Player[1].nLoss = 0;
			Player[1].nDraw = 0;		
		}
		else{
			printf("It is a draw\n\n");
			Player[0].nWin = 0;
			Player[0].nLoss = 0;
			Player[0].nDraw = 1;
			Player[1].nWin = 0;
			Player[1].nLoss = 0;
			Player[1].nDraw = 1;
		}
	}
    
    for(int j = 0; j < 3; j++)
    	for(int k = 0; k < 3; k++)
    		Player[0].PokeRoster[j][k].nMatchCount = 1;
    		
    for(int l = 0; l < 3; l++){
    	for(int m = 0; m < 3; m++){
    		int nIsSame = 0;
    		for(int n = 0; n < 3; n++)
    			for(int o = 0; o < 3; o++)
    				if(strcmp(Player[0].PokeRoster[n][o].szPetName, Player[1].PokeRoster[l][m].szPetName) == 0)
    					nIsSame = 1;
			
			if(!nIsSame)
				Player[1].PokeRoster[l][m].nMatchCount = 1;
		}
	}
    
    SaveMatchResults(Player, BattleGrid);
    SavePlayerResults(Player, PlayerList, nPlayerCount); //function call to save the information of the current players	
    UpdateCompetdium(Player, PetList, nPetCount); //function call to save the information of the current players
}


/**
* The function Horizontal checks how many horizontal lucky wins the player has.
* @param grid[][] is an int array storing the result of the battle between player 1 and player 2 in each cell (1 - player 1 wins, 2 - player 2 wins, 0 - draw)
* @param num is the number that the function will check to see if it aligns horizontally. The num variable changes depending on the player (1 for player 1, 2 for player 2)
* @return the amount of horizontal wins
* @pre grid already stores the result of the battle between the two players and num is either 1 or 2
*/
int Horizontal(int grid[][3], int num){
  int x, z = 0;
  
  //this for loop goes to each row to check if each has a horizontal win
  for(x = 0; x < 3; x++)
      if(grid[x][0] == num && grid[x][1] == num && grid[x][2] == num)
        z++;
  
  return z;
}



/**
* The function Vertical checks how many vertical lucky wins the player has.
* @param grid[][] is an int array storing the result of the battle between player 1 and player 2 in each cell (1 - player 1 wins, 2 - player 2 wins, 0 - draw)
* @param num is the number that the function will check to see if it aligns vertically. The num variable changes depending on the player (1 for player 1, 2 for player 2)
* @return the amount of vertical wins
* @pre grid already stores the result of the battle between the two players and num is either 1 or 2
*/
int Vertical(int grid[][3], int num){
  	int x, z = 0;
 
 	//this for loop goes to each column to check if each has a vertical win
	for(x = 0; x < 3; x++)
		if(grid[0][x] == num && grid[1][x] == num && grid[2][x])
    		z++;
  
  return z;
}



/**
* The function Diagonal checks how many diagonal lucky wins the player has.
* @param grid[][] is an int array storing the result of the battle between player 1 and player 2 in each cell (1 - player 1 wins, 2 - player 2 wins, 0 - draw)
* @param num is the number that the function will check to see if it aligns diagonally. The num variable changes depending on the player (1 for player 1, 2 for player 2)
* @return the amount of diagonal wins
* @pre grid already stores the result of the battle between the two players and num is either 1 or 2
*/
int Diagonal(int grid[][3], int num){
	int z = 0;
  	
  	//this if statement checks if there is a diagonal win
  	if(grid[0][0] == num && grid[1][1] == num && grid[2][2] == num)
  		z++;
  	//this if statement checks if there is an antidiagonal (the opposite direction of diagonal) win
  	if(grid[0][2] == num && grid[1][1] == num && grid[2][0] == num)
  		z++;
  
  return z;
}
