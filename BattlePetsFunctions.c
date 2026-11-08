//function called when the battle option in the main file is chosen
void BattleMenu(Grid PetList[], int nMaxPetCount){
  FILE *fp;
  int nChoice, nChoice2;
  int nPetCount = 0;
  char szPetOfChoice[37];

  for(int nCurrentPlayer = 0; nCurrentPlayer < 2; nCurrentPlayer++){
	  printf("+------------------------------------+\n");
	  printf("|             Player %d              |\n", i + 1);
	  printf("+-----------+------------------------+\n");
	  printf("|     1     |      <New Player>      |\n");
	  printf("+-----------+------------------------+\n");
	  //if((fp = fopen("players.txt", "r") != NULL))   to be implemented when the presaved usernames thing has been figured out
	  printf("> ");
	  scanf("%d", &nChoice);

      switch (nChoice){
	  	case 1:
        	printf("Enter username: ");
        	scanf("%s", PlayerInfo[nCurrentPlayer].szPlayerName);
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
				case 1: Competdium(nCurrentPlayer, nChoice2);
						printf("+------------------------------------+\n");
  						printf("|            Competdium              |\n");
	  					printf("+------------------------------------+\n");

						for(int k = 0; k < nPetCount; k++){
							printf("%d.\n", k + 1);
							printf("Name: %s\n", PetList[k].szPetName);
							printf("Element: %s", PetList[k].szElement);
							printf("Description: %s", PetList[k].szDescription);
							printf("\n");
						}
							
							
						for(int l = 0; l < 3; l++){
							for(int m = 0; m < 3; m++){
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
								
								do{
									int nIsSame;
									for(int o = 0; o < 3; o++)
										for(int p = 0; p < 3; p++)
											if(strcmp(PlayerInfo[nCurrentPlayer].PokeRoster[o][p].szPetName, szPetOfChoice) == 0)
												nIsSame = 1;
											
									if(nIsSame){
										printf("This pet already exists in your roster.\n");
										printf("> ");
										scanf("%s", szPetOfChoice);
									}
									else
										nIsSame = 0;	
										strcpy(PlayerInfo[nCurrentPlayer].PokeRoster[o][p].szPetName, szPetOfChoice);
								}while(nIsSame);
							}
						}
						
						fclose(fp);	
				  	  	break;		
							
				case 2: Competdium(nCurrentPlayer, nChoice2);
						break;
			}
			
			
			case 2: 
		}
				
        	break;
  	}
  	
  	//battle(); function call
  	
}


void Competdium(int nCurrentPlayer, int nChoice){
    FILE *fp;
    int nPetCount = 0, i = 0;
    
    fp=fopen("competdium.txt","r");
    
    while(fscanf(fp, "%s", PetList[i].szPetName) == 1){
		fscanf((fp,"%s %s %d", PetList[i].szElement, PetList[i].szDescription, &PetList[i].nMatchCount) == 3);
		nPetCount++;
		i++;
    }
    
    switch(nChoice){
    	case 1: printf("+------------------------------------+\n");
  				printf("|            Competdium              |\n");
	  			printf("+------------------------------------+\n");

				for(int k = 0; k < nPetCount; k++){
					printf("%d.\n", k + 1);
					printf("Name: %s\n", PetList[k].szPetName);
					printf("Element: %s", PetList[k].szElement);
					printf("Description: %s", PetList[k].szDescription);
					printf("\n");
				}
				break;
				
		case 2: LoadRoster(nCurrentPlayer);
	}
}

void LoadRoster(int nCurrentPlayer){
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
				printf("Ohhhh we got a newcomer here! Time to give it an element!\n");
				printf("> ");
				scanf("%s", Player[nCurrentPlayer].PokeRoster[l][m].szElement);
			}
		}
	}
}



/*
int battle(ctype Player1[][],cType Player2[][],cType grid){
	int i,g;
    for(i=0;i<3;i++){
        for(g=0;g<3;g++){
    		if(Player2[][].element=="Metal"){
       			if(Player1[][].element=="Water"&&Player1[][].element=="Earth"&&Player1[][].element=="Electric"){
           
       			}
    		}
			else if(Player2[][].element=="Fire"){
        
    		}
    		else if(Player2[][].element=="Water"){
        
    		}
    		else if(Player2[][].element=="Air")
    		{
        
    		}
    		else if(Player2[][].element=="Electric")
    		{
        
    		}
    		else if(Player2[][].element=="Ice")
    		{
        
    		}
    		else if(Player2[][].element=="Earth")
    		{
        
    		}
        }
    }
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
