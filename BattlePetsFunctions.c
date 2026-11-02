void CheckLuckyWin(int Grid[], int n){
  
}

int horizontal(int grid[][],int num){
  int temp=num,x,g,z=0;
  for(x=0;x<3;x++){
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





{
  int i,z;
  for(i=0;i<3,i++){
    for(z=0;z<3;z++){
      grid[i][z]=result(Player1,Player2);//the function which checks whether it is a draw or a win
    }
  }
}



int checkifVerticalorHorizontal(grid[]){
  int temp,z=0,n=0,g=0;
  while(z!=0){
    temp=grid[n][g];
  }
}



