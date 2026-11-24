#ifndef BATTLEPETSFUNCTIONS_H
#define BATTLEPETSFUNCTIONS_H

#define MAX_PETS 60//maximum pets PetList can accomodate
#define PLAYERS 2//number of players
#define MAX_PLAYERS 50//maximum number of players in 

/**
 * Stores the information of each pet
 */
typedef struct {
	char szPetName[37]; //the name of the pet
	char szElement[9]; //the element of the pet
	char szDescription[114]; //the description of the pet
	char Buffer[3]; //used to capture the newline (\n) in between records of two different pets
	int nMatchCount; //the number of matches the pet partook in
}Roster, Grid;

/**
 * Stores the information of each player
 */
typedef struct {
	char szPlayerName[37]; //the name of the player
	int nWin; //the amount of wins of the player
	int nLoss; //the amount of losses of the player
	int nDraw; //the amount of draws of the player
	Roster PokeRoster[3][3]; //the 3x3 roster of the player
}PlayerInfo;

void BattleMenu(Grid PetList[], PlayerInfo PlayerList[], PlayerInfo Player[], int *pPetCount, int *pPlayerCount);
void LoadRoster(Grid PetList[], PlayerInfo Player[], int *pPetCount, int nCurrentPlayer);
void Battle(PlayerInfo Player[], PlayerInfo PlayerList[], Roster Player1Roster[][3], Roster Player2Roster[][3], char *Player1name, char *Player2name, int *pPlayerCount);
int Horizontal(int grid[][3], int num);
int Vertical(int grid[][3], int num);
int Diagonal(int grid[][3], int num);

void PrintAddDeleteEditComp(Grid PetList[], int *pPetCount);
void PrintBattlePets(Grid PetList[], int *pPetCount);
void EditBattlePets(Grid PetList[], int *pPetCount);
void AddBattlePets(Grid PetList[], int *pPetCount);
void DeleteBattlePets(Grid PetList[], int *pPetCount);
void SaveRoster();

#endif
