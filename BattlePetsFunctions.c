//function called when the battle option in the main file is chosen
void BattleMenu(Grid PetList[], PlayerInfo Player[]){
  FILE *fp;
  int nChoice/*this variable stores the choice of the player in choosing a new or existing username*/, nChoice2/*this variable stores whether the player wants to load a saved roster or create a new roster*/;
  int nPetCount = 0;
  char szPetOfChoice[37];

  //this for loop iterate between player 1 and player 2
  for(int nCurrentPlayer = 0; nCurrentPlayer < MAX_PLAYERS; nCurrentPlayer++){
	  printf("+------------------------------------+\n");
	  printf("|             Player %d              |\n", i + 1);
	  printf("+-----------+------------------------+\n");
	  printf("|     1     |      <New Player>      |\n");
	  printf("+-----------+------------------------+\n");
	  //if((fp = fopen("players.txt", "r") == 1))   to be implemented when the presaved usernames thing has been figured out
	  printf("> ");
	  scanf("%d", &nChoice);

      switch (nChoice){
		//case when option 1 is chosen (choosing a new username)
	  	case 1: printf("Enter username: ");
        		scanf("%s", PlayerInfo[nCurrentPlayer].szPlayerName);
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
								
								int nIsSame;
								//this for loop checks if the inputted pet name in szPetOfName is the same as any of the pets in the current player's roster
								for(int o = 0; o < 3; o++)
									for(int p = 0; p < 3; p++)
										//this if statement executes whenever szPetOFChoice is the same as any of the pets in the current player's grid
										if(strcmp(PlayerInfo[nCurrentPlayer].PokeRoster[o][p].szPetName, szPetOfChoice) == 0)
											nIsSame = 1;//the int variable nIsSame evaluates to 1 whenever szPetOfChoice is found to be the same as any pet in the current player's grid
								//this if statement executes when nIsSame == 1, or when szPetOfChoice is found to be the same as any of the pets in the current player's grid	
								if(nIsSame)
									printf("This pet already exists in your roster.\n");
									
								//executetes when nIsSame != 1, or when szPetOfChoice is not found to be the same as any of the pets in the current player's grid, and then szPetOfChoice is put in the current player's gird
								else
									nIsSame = 0; 	
									strcpy(PlayerInfo[nCurrentPlayer].PokeRoster[l][m].szPetName, szPetOfChoice);
							}while(nIsSame);//this do-while loop exits when nIsSame == 0
						}
					}
			  	  	break;		
		}
  	}
  	
  	
  	Battle(Player[0].PokeRoster, Player[1].PokeRoster);//this function is called to have the rosters of the 2 players fight and to store the result of each battle grid cell in an int array
}

//Gets the relevant information from competdium.txt and puts them Grid struct
void Competdium(Grid PetList[], int *nPetCount){
    FILE *fp;
    int i = 0;
    
    fp = fopen("competdium.txt","r");
    
    while(fscanf(fp, "%s", PetList[i].szPetName) == 1){
		fscanf((fp,"%s %s %d", PetList[i].szElement, PetList[i].szDescription, &PetList[i].nMatchCount) == 3);
		nPetCount++;//counts the number of pets received so far
		i++;//index for the array PetList to store relevant information of the pokemon
    }
}

//loads the contents of savedroster/<player_name>.txt onto the roster of the current player (the player indicated by the nCurrentPlayer index)
void LoadRoster(Grid PetList[], PlayerInfo Player[], int *nPetCount, int nCurrentPlayer){
	char bar[35]; //string to stor the name of the txt file containing the saved roster
	
	printf("Please write here the name of the file.\n");
	printf("Note: Please do not include .txt after writing its name because .txt will already be included in the file name by the system.\n");
	printf("(For example: if you type cars.txt, then the system will try to search for cars.txt.txt)\n");
	printf("> ");
    scanf("%s", bar);
    
    strcat(bar, ".txt"); //catenates the string ".txt" to the end of the string contained in the string variable bar

	
	FILE *fp = fopen(bar,"r"); //opens the txt file bearing the same name as in bar to read its contents
    
    for(int j = 0; j < 3; j++)
    	for(int k = 0; k < 3; k++)
	    	fscanf(fp,"%s", Player[nCurrentPlayer].PokeRoster[j][k].szPetName); //puts the pet names of the txt file with the same name as bar into 
    
    fclose(fp);
    
    int nIsSame;
    
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


void Battle(Roster Player1Roster[][3], Roster Player2Roster[][3], Player1name, Player2name){
	int BattleGrid[3][3];
	int Player1, Player2;
	int i,g;
	int count1=0,count2=0;//Basically counts how many 1's or 2's are there
	
    for(i = 0; i < 3; i++){
        for(g = 0; g < 3; g++){
    		if(strcmp(Player1Roster[i][g].szElement, "Fire") == 0){
       			if(strcmp(Player2Roster[i][g].szElement, "Grass") == 0 || strcmp(Player2Roster[i][g].szElement, "Earth") == 0 || strcmp(Player2Roster[i][g].szElement, "Ice") == 0)
       				BattleGrid[i][g] = 1;
       			else if(strcmp(Player2Roster[i][g].szElement, "Water") == 0 || strcmp(Player2Roster[i][g].szElement, "Metal") == 0)
       				BattleGrid[i][g] = 2;
    			else if(strcmp(Player2Roster[i][g].szElement, "Fire") == 0 || strcmp(Player2Roster[i][g].szElement, "Air") == 0 || strcmp(Player2Roster[i][g].szElement, "Electric") == 0)
       				BattleGrid[i][g] = 0;
			}
       			
           else if(strcmp(Player1Roster[i][g].szElement, "Water") == 0){
    			if(strcmp(Player2Roster[i][g].szElement, "Fire") == 0 || strcmp(Player2Roster[i][g].szElement, "Electric") == 0 || strcmp(Player2Roster[i][g].szElement, "Metal") == 0)
       				BattleGrid[i][g] = 1;
       			else if(strcmp(Player2Roster[i][g].szElement, "Grass") == 0 || strcmp(Player2Roster[i][g].szElement, "Ice") == 0)
       				BattleGrid[i][g] = 2;
       			else if(strcmp(Player2Roster[i][g].szElement, "Water") == 0 || strcmp(Player2Roster[i][g].szElement, "Earth") == 0 || strcmp(Player2Roster[i][g].szElement, "Air") == 0)
       				BattleGrid[i][g] = 0;
			}
       		//THE CODE SEGMENTS FROM HERE BELOW ARE INCOMPLETE AND INCORRECT, NEED FIXING
			else if(strcmp(Player1Roster[i][g].szElement, "Grass") == 0){
       			if(strcmp(Player2Roster[i][g].szElement, "Water") == 0 || strcmp(Player2Roster[i][g].szElement, "Earth") == 0 || strcmp(Player2Roster[i][g].szElement, "Electric") == 0)
       				BattleGrid[i][g] = 1;
    			else if(strcmp(Player2Roster[i][g].szElement, "Fire") == 0 || strcmp(Player2Roster[i][g].szElement, "Air") == 0 || strcmp(Player2Roster[i][g].szElement, "Ice") == 0)
       				BattleGrid[i][g] = 2;
       			else if(strcmp(Player2Roster[i][g].szElement, "Grass") == 0 || strcmp(Player2Roster[i][g].szElement, "Metal") == 0)
       				BattleGrid[i][g] = 0;
			}
			
			else if(strcmp(Player1Roster[i][g].szElement, "Earth") == 0){
       			if(strcmp(Player2Roster[i][g].szElement, "Air") == 0 || strcmp(Player2Roster[i][g].szElement, "Metal") == 0)
       				BattleGrid[i][g] = 1;
    			else if(strcmp(Player2Roster[i][g].szElement, "Fire") == 0 || strcmp(Player2Roster[i][g].szElement, "Grass") == 0 || strcmp(Player2Roster[i][g].szElement, "Electric") == 0)
       				BattleGrid[i][g] = 2;
       			else if(strcmp(Player2Roster[i][g].szElement, "Earth") == 0 || strcmp(Player2Roster[i][g].szElement, "Water") == 0 || strcmp(Player2Roster[i][g].szElement, "Ice") == 0)
       				BattleGrid[i][g] = 0;
			}
			
			else if(strcmp(Player1Roster[i][g].szElement, "Air") == 0){
       			if(strcmp(Player2Roster[i][g].szElement, "Grass") == 0 || strcmp(Player2Roster[i][g].szElement, "Electric") == 0)
       				BattleGrid[i][g] = 1;
    			else if(strcmp(Player2Roster[i][g].szElement, "Earth") == 0 || strcmp(Player2Roster[i][g].szElement, "Ice") == 0 || strcmp(Player2Roster[i][g].szElement, "Metal") == 0)
       				BattleGrid[i][g] = 2;
       			else if(strcmp(Player2Roster[i][g].szElement, "Air") == 0 || strcmp(Player2Roster[i][g].szElement, "Fire") == 0 || strcmp(Player2Roster[i][g].szElement, "Water") == 0)
       				BattleGrid[i][g] = 0;
			}
			
			else if(strcmp(Player1Roster[i][g].szElement, "Electric") == 0){
       			if(strcmp(Player2Roster[i][g].szElement, "Earth") == 0 || strcmp(Player2Roster[i][g].szElement, "Metal") == 0)
       				BattleGrid[i][g] = 1;
    			else if(strcmp(Player2Roster[i][g].szElement, "Water") == 0 || strcmp(Player2Roster[i][g].szElement, "Grass") == 0 || strcmp(Player2Roster[i][g].szElement, "Air") == 0 || strcmp(Player2Roster[i][g].szElement, "Ice") == 0)
       				BattleGrid[i][g] = 2;
       			else if(strcmp(Player2Roster[i][g].szElement, "Electric") == 0 || strcmp(Player2Roster[i][g].szElement, "Fire") == 0)
       				BattleGrid[i][g] = 0;
			}
			
			else if(strcmp(Player1Roster[i][g].szElement, "Ice") == 0){
       			if(strcmp(Player2Roster[i][g].szElement, "Water") == 0 || strcmp(Player2Roster[i][g].szElement, "Grass") == 0 || strcmp(Player2Roster[i][g].szElement, "Air") == 0 || strcmp(Player2Roster[i][g].szElement, "Electric") == 0)
       				BattleGrid[i][g] = 1;
    			else if(strcmp(Player2Roster[i][g].szElement, "Fire") == 0 || strcmp(Player2Roster[i][g].szElement, "Metal") == 0)
       				BattleGrid[i][g] = 2;
       			else if(strcmp(Player2Roster[i][g].szElement, "Ice") == 0 || strcmp(Player2Roster[i][g].szElement, "Earth") == 0)
       				BattleGrid[i][g] = 0;
			}
			
			else if(strcmp(Player1Roster[i][g].szElement, "Metal") == 0){
       			if(strcmp(Player2Roster[i][g].szElement, "Fire") == 0 || strcmp(Player2Roster[i][g].szElement, "Air") == 0 || strcmp(Player2Roster[i][g].szElement, "Ice") == 0)
       				BattleGrid[i][g] = 1;
    			else if(strcmp(Player2Roster[i][g].szElement, "Water") == 0 || strcmp(Player2Roster[i][g].szElement, "Earth") == 0 || strcmp(Player2Roster[i][g].szElement, "Electric") == 0)
       				BattleGrid[i][g] = 2;
       			else if(strcmp(Player2Roster[i][g].szElement, "Metal") == 0 || strcmp(Player2Roster[i][g].szElement, "Grass") == 0)
       				BattleGrid[i][g] = 0;
			}
        }
    }

	//PrintMatchResults(BattleGrid);
	Player1 = horizontal(BattleGrid, 1) + vertical(BattleGrid,1) +diagonal(BattleGrid,1);
	Player2 = horizontal(BattleGrid, 2) + vertical(BattleGrid,2) +diagonal(BattleGrid,2);


	if(Player1>Player2)
	{
		printf("Winner: %s (Player 1) [Lucky Win]", Player1name);
	
	}
    else if(Player2>Player1)
	{
		printf("Winner: %s (Player 2) [Lucky Win]", Player2name);
	
	}
	else
	{
	for(i=0;i<3;i++)
		{
			for(g=0;g<3;g++)
				{
					if(BattleGrid[i][g]==1)
					{
						count1+=1;
					}
					if(BattleGrid[i][g]==2)
					{
						count2+=1;
					}
				}
		}
		if(count1>count2)
		{
			printf(Winner: %s (Player 1) [Majority Win],Player1name);
		}
		else if(count1>count2)
		{
			printf(Winner: %s (Player 2) [Majority Win],Player2name);
		}
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

int horizontal(int grid[][], int num){
  int x, z = 0;
  for(x = 0; x < 3; x++)
      if(grid[x][0] == num && grid[x][1] == num && grid[x][2] == num)
        z++;
  
  return z;
}


int vertical(int grid[][], int num){
  int x, z = 0;
 
    for(x = 0; x < 3; x++)
      if(grid[0][x] == num && grid[1][x] == num && grid[2][x])
        z++;
  
  return z;
}


int diagonal(int grid[][], int num){
  int z = 0;
  
  if(grid[0][0] == num && grid[1][1] == num && grid[2][2] == num)
  	z++;
  	
  if(grid[0][2] == num && grid[1][1] == num && grid[2][0] == num)
  	z++;
  
  return z;
}
