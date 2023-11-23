#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <unistd.h>
#include <stdlib.h>

void PrintNewLine(){
    printf("\n");
}

const int PLAYER_X = 0;
const int PLAYER_O = 1;
const int EMPTY = -1;

int GameState[3][3];

void CreateNewGame(){
    for (size_t i = 0; i < 3; i++)
    {
       for (size_t j = 0; j < 3; j++)
       {
        GameState[i][j] = EMPTY;
       }
    }   
}
void ShowBoard() {
    printf("   0   1   2");
    PrintNewLine();
    printf(" ┌───────────┐");
    PrintNewLine();
    for (int x = 0; x < 3; x++)
    {
        printf("%d", x);
        printf("│");
        for (int y = 0; y < 3; y++)
        {
            int value = GameState[x][y];
            if (value == EMPTY) {
                printf("   |"); 
            }else if (value == PLAYER_X)
            {
                printf(" x |");
            }else if(value == PLAYER_O){
                printf(" o |");
            }
        }
        if(x < 2){
            printf("\n ├───┼───┼───┤\n");
        }
    } 
    PrintNewLine();
    printf(" └───────────┘\n");
}

bool isValidPosition(int x,int y){
    if(x > 2 || x < 0 ){
        return false;
    }
    if(y > 2 || y < 0){
        return false;
    }
    if (GameState[x][y] != EMPTY){
        return false;
    }
    return 1;
}

void Play(int x,int y,int player, bool* p_xturn){
    if(isValidPosition(x,y)){
        GameState[x][y] = player;
        *p_xturn = !(*p_xturn);
    }
}


bool thereIsEmptyCase(){
    for (size_t x = 0; x < 3; x++)
    {
       for (size_t y = 0; y < 3; y++)
       {
        if (GameState[x][y] == EMPTY )
        {
            return true;
        }
       }
    }
    return false;
}

int checkIfWinner(){
    int firstValueRow;
    for (size_t row = 0; row < 3; row++)
    {
        firstValueRow = GameState[row][0];
        int col=0; 
        for (col = 0; col < 3; col++)
        {
            if(GameState[row][col] == firstValueRow && firstValueRow != EMPTY){
                continue;
            }else{
                break;
            }
        }
        if(col == 3){
            return firstValueRow;
        }
    }

    int firstValueCol;
    for (size_t col = 0; col < 3; col++)
    {
        firstValueCol = GameState[0][col];
        int row=0; 
        for (row = 0; row < 3; row++)
        {
            if(GameState[row][col] == firstValueCol && firstValueCol != EMPTY){
                continue;
            }else{
                break;
            }
        }
        if(row == 3){
            return firstValueCol;
        }
    }
    int firstValueDiagonal = GameState[0][0];
    int row=0;
    int col=0;
    for (row = 0; row < 3; row++)
    {
        if(GameState[row][col] == firstValueDiagonal && firstValueDiagonal != EMPTY){
            col++;
            continue;
        }else{
            break;
        }
    }
    if(row == 3){
        return firstValueDiagonal;
    }
    int firstValueAntiDiagonal = GameState[0][2];
    int rowAnti=0;
    int colAnti=2;
    for (rowAnti = 0; rowAnti < 3; rowAnti++)
    {
        if(GameState[rowAnti][colAnti] == firstValueAntiDiagonal && firstValueAntiDiagonal != EMPTY){
            colAnti--;
            continue;
        }else{
            break;
        }
    }
    if(rowAnti == 3){
        return firstValueAntiDiagonal;
    }

    return -1;
}

bool isGameFinished(){

    int winner = checkIfWinner();
    if(winner == PLAYER_X)
    {
        printf("the winner is X\n");
        return true;
    }else if (winner == PLAYER_O)
    {
        printf("the winner is O\n");
        return true;
    }else{
        if(!thereIsEmptyCase()){
            return true;
        }
        return false;
    }
}

void Game(){
    int x,y;
    CreateNewGame();
    bool xturn = true;
    while (!isGameFinished())
    {
        ShowBoard();
        PrintNewLine();

        if(xturn){
            printf("player x turn, enter x and y:\n");
            fflush(stdout);
            if(scanf("%d %d", &x,&y) == 2){
                Play(x,y,PLAYER_X,&xturn);
            };
            getchar();
        }else{
            printf("player o turn, enter x and y:\n");
            fflush(stdout);
            if(scanf("%d %d", &x,&y) == 2){
                Play(x,y,PLAYER_O,&xturn);
            }
            getchar();
        }
        system("clear");
    }
}


int main(){
    Game();
}