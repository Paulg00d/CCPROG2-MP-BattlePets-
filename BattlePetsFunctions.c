//function called when the battle option in the main file is chosen
void BattleMenu(Grid PetList[], PlayerInfo Player[]){
  FILE *fp;
  int nChoice, nChoice2;
  int nPetCount = 0;
  char szPetOfChoice[37];

  for(int nCurrentPlayer = 0; nCurrentPlayer < MAX_PLAYERS; nCurrentPlayer++){
	  printf("+------------------------------------+\n");
	  printf("|             Player %d              |\n", i + 1);
	  printf("+-----------+------------------------+\n");
	  printf("|     1     |      <New Player>      |\n");
	  printf("+-----------+------------------------+\n");
	  //if((fp = fopen("players.txt", "r") != NULL))   to be implemented when the presaved usernames thing has been figured out
	  printf("> ");
	  scanf("%d", &nChoice);

      switch (nChoice){
	  	case 1: printf("Enter username: ");
        		scanf("%s", PlayerInfo[nCurrentPlayer].szPlayerName);
				break;
		/*case 2: 
				break;*/
	   }
		
		printf("+------------------------------------+\n");
	  	printf("|  Time to choose your battle pets!  |\n", i + 1);
	  	printf("+-----------+------------------------+\n");
	  	printf("|     1     |     Open Competdium    |\n");
	  	printf("+-----------+------------------------+\n");
	  	printf("|     2     |    Load saved roster   |\n");
	  	printf("+-----------+------------------------+\n");
		printf("> ");
		scanf("%d", &nChoice2);
		
		switch(nChoice2){
			case 1: Competdium(PetList, &nPetCount);
					
					printf("+------------------------------------+\n");
  					printf("|            Competdium              |\n");
	  				printf("+------------------------------------+\n");

					for(int k = 0; k < nPetCount; k++){
						printf("%d.\n", k + 1);
						printf("Name: %s\n", PetList[k].szPetName);
						printf("Element: %s\n", PetList[k].szElement);
						printf("Description: %s\n\n", PetList[k].szDescription);
					}
						
					for(int l = 0; l < 3; l++){
						for(int m = 0; m < 3; m++){
							do{
								printf("> ");
								scanf("%s", szPetOfChoice);
								int nPetFound = 0;
								
								while(!nPetFound){
									for(int n = 0; n < nPetCount; n++)
										if(strcmp(PetList[n].szPetName, szPetOfChoice) == 0)
											nPetFound = 1;
									if(!nPetFound){
										printf("Pet not found.\n");
										printf("> ");
										scanf("%s", szPetOfChoice);
									}
								}
								
								int nIsSame;
								for(int o = 0; o < 3; o++)
									for(int p = 0; p < 3; p++)
										if(strcmp(PlayerInfo[nCurrentPlayer].PokeRoster[o][p].szPetName, szPetOfChoice) == 0)
											nIsSame = 1;
											
								if(nIsSame)
									printf("This pet already exists in your roster.\n");
								else
									nIsSame = 0;	
									strcpy(PlayerInfo[nCurrentPlayer].PokeRoster[l][m].szPetName, szPetOfChoice);
							}while(nIsSame);
						}
					}	
			  	  	break;		
							
			case 2: Competdium(nCurrentPlayer, &nPetCount);
					LoadRoster(Player, &nPetCount);
					break;
		}
  	}
  	
  	Battle(Player[0].PokeRoster, Player[1].PokeRoster);
}

void Competdium(Grid PetList[], int *nPetCount){
    FILE *fp;
    int i = 0;
    
    fp = fopen("competdium.txt","r");
    
    while(fscanf(fp, "%s", PetList[i].szPetName) == 1){
		fscanf((fp,"%s %s %d", PetList[i].szElement, PetList[i].szDescription, &PetList[i].nMatchCount) == 3);
		nPetCount++;
		i++;
    }
}

void LoadRoster(PlayerInfo Player, int *nPetCount, int nCurrentPlayer){
	FILE *fp = fopen("roster.txt","r");//this is not the final
    
    for(int j = 0; j < 3; j++)
    	for(int k = 0; k < 3; k++)
	    	fscanf(fp,"%s", Player[nCurrentPlayer].PokeRoster[j][k].szPetName);
    
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
			if(!nIsSame){
				printf("Ohhhh we got a newcomer here! Time to give %s an element!\n", Player[nCurrenPlayer].PokeRoster[l][m].szPetName);
				printf("> ");
				scanf("%s", Player[nCurrentPlayer].PokeRoster[l][m].szElement);
			}
		}
	}
}


void Battle(Roster Player1Roster[][3], Roster Player2Roster[][3]){
	int BattleGrid[3][3];
	
	int i,g;
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
    
    //horizontal(BattleGrid); this function calls the function horizontal() to check for any horizontal wins.
}


int horizontal(int grid[][],int num){
  int temp=num,x,g,z;
  for(x=0;x<3;x++){
    z=0;
    for(g=0;g<3;g++){
      if(temp==grid[x][g]){
        z++;
        if(z==3)
          return 1;
      }
    }
  }
  
  return 0;
}


int vertical(int grid[][],int num){
  int temp=num,x,g,z=0;
  for(x=0;x<3;x++){
    for(g=0;g<3;g++){
      if(temp==grid[g][x]){
        z++;
        if(z==3)
          return 1;
      }
    }
  }
  return 0;
}


int diagonal(int grid[][],int num){
  int temp=num,x,g=0,z=0;
    for(x=0;x<3:x++){
      if(temp==grid[x][g]){
        z++;
      }
      g++;
      if(z==3)
        return num;
  }

  for(x=2;x>=0:x--){
    if(temp==grid[x][g]){
      z++;
    }
    g++;
    if(z==3)
      return num;
  }
  
  return 0;
}
*/
