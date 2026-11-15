#ifndef BATTLEPETSFUNCTIONS_H
#define BATTLEPETSFUNCTIONS_H

/**
 * Stores information of each pet
 */
typedef struct {
	char szPetName[37]; //the name of the pet
	char szElement[9]; //the element of the pet
	char szDescription[114]; //the description of the pet
	int nMatchCount; //the number of matches the pet partook in
}Roster, Grid;

/**
 * Stores information of each player
 */
typedef struct {
	char szPlayerName[37]; //the name of the player
	Roster PokeRoster[3][3]; //the 3x3 roster of the player
}PlayerInfo;

void BattleMenu(Grid PetList[], PlayerInfo Player[]);
void Competdium(Grid PetList[], int *nPetCount);
void LoadRoster(Grid PetList[], PlayerInfo Player[], int *nPetCount, int nCurrentPlayer);
int Battle(Roster Player1Roster[][3], Roster Player2Roster[][3], char *Player1name, char *Player2name);
int Horizontal(int grid[][3], int num);
int Vertical(int grid[][3], int num);
int Diagonal(int grid[][3], int num);

#endif
