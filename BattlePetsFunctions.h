#ifndef BATTLEPETSFUNCTIONS_H
#define BATTLEPETSFUNCTIONS_H

typedef struct {
	char szPetName[37];
	char szElement[9];
	char szDescription[114];
	int nMatchCount;
}Roster, Grid;

typedef struct {
	char szPlayerName[37];
	Roster PokeRoster[3][3];
}PlayerInfo;

void BattleMenu(Grid PetList[], PlayerInfo Player[]);
void Competdium(Grid PetList[], int *nPetCount);
void LoadRoster(Grid PetList[], PlayerInfo Player[], int *nPetCount, int nCurrentPlayer);
int Battle(Roster Player1Roster[][3], Roster Player2Roster[][3], char *Player1name, char *Player2name);
int Horizontal(int grid[][3], int num);
int Vertical(int grid[][3], int num);
int Diagonal(int grid[][3], int num);

#endif
