void BattleMenu(){
  FILE *fp;
  int nChoice;

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
			for(int i = 0; i < 2; i++){
        		printf("Enter username: ");
        		scanf("%s", PlayerInfo[i].szPlayerName);
				int nChoice2;
				printf("+------------------------------------+\n");
	  			printf("|   Time to choose your battle pets! |\n", i + 1);
	  			printf("+-----------+------------------------+\n");
	  			printf("|     1     |     Open Competdium    |\n");
	  			printf("+-----------+------------------------+\n");
	  			printf("|     2     |    Load saved roster   |\n");
	  			printf("+-----------+------------------------+\n");
				printf("> ");
				scanf("%d", &nChoice2);
				switch(nChoice2){
					case 1:
						fp = fopen("competdium.txt", "r");
						for(int j = 0; j < 9; i++){
							
			} 
				
        	break;

	/*
	int i,g;
    for(i=0;i<3;i++)
    {
        for(g=0;g<3;g++)
        {
    if(Player2[][].element=="Metal")
    {
       if(Player1[][].element=="Water"&&Player1[][].element=="Earth"&&Player1[][].element=="Electric")
       {
           
       }
    }
    else if(Player2[][].element=="Fire")
    {
        
    }
    else if(Player2[][].element=="Water")
    {
        
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
	not yet complete, to be connected to the rest of the function later on */
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


