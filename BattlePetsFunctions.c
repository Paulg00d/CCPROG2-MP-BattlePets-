//function called when the battle option in the main file is chosen
void BattleMenu(){
  FILE *fp;
  int nChoice, nChoice2;
  int nPetCount = 0;
  char szPetOfChoice[37];

  for (int i = 0; i < 2; i++){
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
        	scanf("%s", PlayerInfo[i].szPlayerName);
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
				case 1: fp = fopen("competdium.txt", "r");
						for(int j = 0; (fscanf(fp, "%s", PetList[j].szPetName)) == 1; i++){
							fscanf(fp, "%s", PetList[j].szElement);
							fscanf(fp, "%s", PetList[j].szDescription);
							nPetCount++;
						}

						printf("+------------------------------------+\n");
  						printf("|            Competdium              |\n");
	  					printf("+------------------------------------+\n");

						for(int k = 0; k < nPetCount; k++)
							printf("%d. %s\n", k + 1, PetList[k].szPetName);
							
						for(int l = 0; l < 3; l++){
							for(int m = 0; m < 3; m++){
								printf("> ");
								scanf("%s", szPetOfChoice);
								
								for(int n = 0; n < 3; n++){
									for(int o = 0; o < 3; o++){
										while(strcmp(PlayerInfo[i].szPokeRoster[n][o], szPetOfChoice) == 0){
											printf("Batte pet already selected, please try again.\n");
											printf("> ");
											scanf("%s", szPetOfChoice);
										}
									}
								}
								
								PlayerInfo[i].szPokeRoster[l][m] = szPetOfChoice;
							}
						}
						fclose(fp);	
				  	  	break;
				  	  
				//case 2:
						
			}
			
			case 2: 
		}
				
        	break;
  	}
  	
  	//battle(); function call
  	
}

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


