#include <stdio.h>
#include <string.h>
#include "BattlePetsFunctions.h"

/*	The function BattleMenu is called when the player chooses the first option (Battle!) in the main menu
	@param PetList is an array of structs, with each struct containing the information of each battle pet (name, element, description, match count)
	@param Player is an array of structs, with each struct containing the information of each player (name, roster), of which there are two
*/
void BattleMenu(Grid PetList[], PlayerInfo Player[]){
  FILE *fp;
  int nChoice;/*this variable stores the choice of the player in choosing a new or existing username*/
  int nChoice2;/*this variable stores whether the player wants to load a saved roster or create a new roster*/
  int nPetCount = 0;
  char szPetOfChoice[37];

  //this for loop iterate between player 1 and player 2
  for(int nCurrentPlayer = 0; nCurrentPlayer < MAX_PLAYERS; nCurrentPlayer++){
	  printf("+------------------------------------+\n");
	  printf("|             Player %d              |\n", nCurrentPlayer + 1);
	  printf("+-----------+------------------------+\n");
	  printf("|     1     |      <New Player>      |\n");
	  printf("+-----------+------------------------+\n");
	  //if((fp = fopen("players.txt", "r") == 1))   to be implemented when the presaved usernames thing has been figured out
	  printf("> ");
	  scanf("%d", &nChoice);

      switch (nChoice){
		//case when option 1 is chosen (choosing a new username)
	  	case 1: printf("Enter username: ");
        		scanf("%s", Player[nCurrentPlayer].szPlayerName);
				break;
		//case when the player chooses to use an existing username
		/*case 2: 
				break;*/
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
			case 1: Competdium(PetList, &nPetCount); //loads the contents of Competdium into an array of structs called PetList
					LoadRoster(PetList, Player, &nPetCount, nCurrentPlayer); //loads the contents of savedroster/<player_name>.txt onto the roster of the current player (the player indicated by the nCurrentPlayer index)
					break;
			//chosen when the player chooses to create their own roster for the game
			case 2: Competdium(PetList, &nPetCount);//loads the contents of Competdium into an array of structs called PetList
					
					printf("+------------------------------------+\n");
  					printf("|            Competdium              |\n");
	  				printf("+------------------------------------+\n");
					//this for loop prints the contents of the PetList array which stores the contents of competdium.txt
					for(int k = 0; k < nPetCount; k++){
						printf("%d.\n", k + 1);//prints the number for the current pet (e.g. 1., 2.)
						printf("Name: %s\n", PetList[k].szPetName);//displays the name of the pet
						printf("Element: %s\n", PetList[k].szElement);//displays the element of the pet
						printf("Description: %s\n\n", PetList[k].szDescription);//displays the description of the pet
					}
					//this for loop iterates each cell of the current player's grid
					for(int l = 0; l < 3; l++){//iterates between rows
						for(int m = 0; m < 3; m++){//iterates between columns
							//this do-while loop executes until the int variable nIsSame == 0 to make sure the entered pet name is not the same as any pet in the current player's grid
							int nIsSame;
							do{
								printf("> ");
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
								for(int o = 0; o < 3; o++)
									for(int p = 0; p < 3; p++)
										//this if statement executes whenever szPetOFChoice is the same as any of the pets in the current player's grid
										if(strcmp(Player[nCurrentPlayer].PokeRoster[o][p].szPetName, szPetOfChoice) == 0)
											nIsSame = 1;//the int variable nIsSame evaluates to 1 whenever szPetOfChoice is found to be the same as any pet in the current player's grid
								//this if statement executes when nIsSame == 1, or when szPetOfChoice is found to be the same as any of the pets in the current player's grid	
								if(nIsSame)
									printf("This pet already exists in your roster.\n");
									
								//executetes when nIsSame != 1, or when szPetOfChoice is not found to be the same as any of the pets in the current player's grid, and then szPetOfChoice is put in the current player's gird
								else{
									nIsSame = 0; 	
									strcpy(Player[nCurrentPlayer].PokeRoster[l][m].szPetName, szPetOfChoice);
								}
							}while(nIsSame);//this do-while loop exits when nIsSame == 0
						}
					}
			  	  	break;		
		}
  	}
  	
  	
  	Battle(Player[0].PokeRoster, Player[1].PokeRoster, Player[0].szPlayerName, Player[1].szPlayerName);//this function is called to have the rosters of the 2 players fight and to store the result of each battle grid cell in an int array
}

/*	The function Competdium gets the relevant information from competdium.txt and puts them int the PetList grid struct
	@param PetList is an array of structs, with each struct containing the information of each battle pet (name, element, description, match count)
	@param @param *nPetCount is an int pointer pointing to the an int variable containing the number of pets stored in PetList so far (maximum is 60) to be modified in the function
*/
void Competdium(Grid PetList[], int *nPetCount){
    FILE/*error because no stdio.h*/ *fp;
    int i = 0;
    
    fp = fopen/*error because no stdio.h*/("competdium.txt","r");//opens the txt file competdium.txt to read all of its contents
    
    //this while loop executes for as long as it can read the pet name found in competdium.txt into PetList
    while(fscanf/*error because no stdio.h*/(fp, "%s", PetList[i].szPetName) == 1){
/*error because left-hand operand of comma expression has no effect*/		fscanf((fp,"%s %s %d", PetList[i].szElement, PetList[i].szDescription, &PetList[i].nMatchCount) == 3/*error because comparison between pointer and integer*/); //reads all the other relevant information (element, description, match count)
		nPetCount++;//increments every time all the information of a pet have been successfully read
		i++;//index of the array PetList for each pet
    }
}

/*	The function LoadRoster loads the contents of savedroster/<player_name>.txt onto the roster of the current player (the player indicated by the nCurrentPlayer index)
	@param PetList[] is an array of structs, with each struct containing the information of each battle pet (name, element, description, match count)
	@param Player is an array of structs, with each struct containing the information of each player (name, roster), of which there are two
	@param *nPetCount is an int pointer pointing to the an int variable containing the number of pets stored in PetList so far (maximum is 60)
	@param nCurrentPlayer is the index of the Player[] array of structs indicating the current player
*/
void LoadRoster(Grid PetList[], PlayerInfo Player[], int *nPetCount, int nCurrentPlayer){
	char bar[35]; //string to stor the name of the txt file containing the saved roster
	
	printf("Please write here the name of the file.\n");
	printf("Note: Please do not include .txt after writing its name because .txt will already be included in the file name by the system.\n");
	printf("(For example: if you type cars.txt, then the system will try to search for cars.txt.txt)\n");
	printf("> ");
    scanf("%s", bar);
    
    strcat(bar, ".txt"); //catenates the string ".txt" to the end of the string contained in the string variable bar

	
	FILE *fp = fopen(bar,"r"); //opens the txt file bearing the same name as bar to read its contents
    
    //this for loop goes to each cell of the current player's grid
    for(int j = 0; j < 3; j++)
    	for(int k = 0; k < 3; k++)
	    	fscanf(fp,"%s", Player[nCurrentPlayer].PokeRoster[j][k].szPetName); //puts the pet names of the txt file with the same name as bar into each cell of the current player's grid
    
    fclose(fp);
    
    int nIsSame;//flag to check if any of the pets in the player's saved roster is found in competdium. For each cell in the player's grid, it evaluates to 1 if it is found in competdium, and 0 if otherwise
    
    //this for loop goes to each cell of the player's roster grid to check if the pet in the current cell is found in competdium or not
    for(int l = 0; l < 3; l++){
    	for(int m = 0; m < 3; m++){
    		nIsSame = 0;
        	for(int n = 0; n < nPetCount; n++){
        		if(strcmp(Player[nCurrentPlayer].PokeRoster[l][m].szPetName, PetList[n].szPetName) == 0){
        			strcpy(Player[nCurrentPlayer].PokeRoster[l][m].szElement, PetList[n].szElement);
        			nIsSame = 1;
				}
			}
			if(nIsSame == 0){
				printf("Ohhhh we got a newcomer here! Time to give %s an element!\n", Player[nCurrenPlayer].PokeRoster[l][m].szPetName);
				printf("> ");
				scanf("%s", Player[nCurrentPlayer].PokeRoster[l][m].szElement);
			}
		}
	}
}

/*	The function Battle stores the result of the fight between the rosters of the two players. Whichever pet wins, loses, or neither in each grid cell is stored in a new grid
	@param Player1Roster is the roster of Player 1 in the form of a 2d array of structs, where each struct stores the name and element of each player
	@param Player2Roster is the roster of Player 2 in the form of a 2d array of structs, where each struct stores the name and element of each player
	@param Player1name is the username of player 1
	@param Player2name is the username of player 2
*/
void Battle(Roster Player1Roster[][3], Roster Player2Roster[][3], char *Player1name, char *Player2name){
	int BattleGrid[3][3];//an int array to display if one player won or if it is a tie in each cell (1 - player 1 wins, 2 - player 2 wins, 0 - it is a draw)
	int Player1/*an int variable to contain how many lucky wins player 1 has (e.g. 2 horizontal wins, 2 vertical wins)*/, Player2/*an int variable to contain how many lucky wins player 2 has (e.g. 2 horizontal wins, 2 vertical wins)*/;
	int i, g;//int variables to go to each cell in each of the two player rosters and in BattleGrid[][]
	int count1=0,count2=0;//Basically counts how many 1's or 2's are there
	
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

	Player1 = Horizontal(BattleGrid, 1) + Vertical(BattleGrid, 1) + Diagonal(BattleGrid, 1);//Player1 calls the functions show to store how many lucky wins player 1 has
	Player2 = Horizontal(BattleGrid, 2) + Vertical(BattleGrid, 2) + Diagonal(BattleGrid, 2);//Player2 calls the functions show to store how many lucky wins player 2 has


	if(Player1>Player2)//executes if player 1 has more lucky wins than player 2
	{
		printf("Winner: %s (Player 1) [Lucky Win]", Player1name);
	
	}
    else if(Player2>Player1)//executes if player 2 has more lucky wins than player 1
	{
		printf("Winner: %s (Player 2) [Lucky Win]", Player2name);
	
	}
	else//executes if neither player has any lucky wins or if both have the same number of lucky wins (e.g. both player 1 and player 2 have 1 horizontal win each)
	{
	//this for loop goes to each cell of BattleGrid to count how many 1's and/or 2's there are
	for(i=0;i<3;i++)
		{
			for(g=0;g<3;g++)
				{
					if(BattleGrid[i][g]==1)
					{
						count1+=1;//increments whenever 1 is in the cell [i][g]
					}
					if(BattleGrid[i][g]==2)
					{
						count2+=1;//increments whenever 2 is in the cell [i][g]
					}
				}
		}
		if(count1>count2)//executes if player 1 has more wins than player 2
		{
			printf("Winner: %s (Player 1) [Majority Win]", Player1name);
		}
		else if(count1>count2)//executes if player 2 has more wins than player 1
		{
			printf("Winner: %s (Player 2) [Majority Win]", Player2name);
		}
		else
			printf("It is a draw")
	}
    
    //horizontal(BattleGrid); this function calls the function horizontal() to check for any horizontal wins.
}

/*
void PrintMatchResults(int BattleGrid[][3]){
	printf("+---+---+---+\n");
	for(int i = 0; i < 3; i++)
		for(int j = 0; j < 3; j++){
			
		}
}
*/

int Horizontal(int grid[][3], int num){
  int x, z = 0;
  for(x = 0; x < 3; x++)
      if(grid[x][0] == num && grid[x][1] == num && grid[x][2] == num)
        z++;
  
  return z;
}


int Vertical(int grid[][3], int num){
  int x, z = 0;
 
    for(x = 0; x < 3; x++)
      if(grid[0][x] == num && grid[1][x] == num && grid[2][x])
        z++;
  
  return z;
}


int Diagonal(int grid[][3], int num){
  int z = 0;
  
  if(grid[0][0] == num && grid[1][1] == num && grid[2][2] == num)
  	z++;
  	
  if(grid[0][2] == num && grid[1][1] == num && grid[2][0] == num)
  	z++;
  
  return z;
}
