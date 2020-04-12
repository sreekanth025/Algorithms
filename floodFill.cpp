#include<bits/stdc++.h>
using namespace std; 

// matrix M*N.
#define M 10
#define N 10

//Possible movements
int row[] = {-1, -1, -1, 0, 0, 1, 1, 1};
int col[] = {-1, 0, 1, -1, 1, -1, 0, 1};

bool isSafe(char mat[][N], int x, int y, char target)
{
    return (x>=0 && x<M)
            && (y>=0 && y<N)
            && (mat[x][y] == target);
}

void floodFill(char mat[M][N], int x, int y, char replacement)
{
    char target = mat[x][y]; 
    mat[x][y] = replacement; 

    for(int k=0; k<8; k++)
        if(isSafe(mat, x+row[k], y+col[k], target))
            floodFill(mat, x+row[k], y+col[k], replacement); 
}

int main()
{
    char mat[M][N] =
    {
        { 'Y', 'Y', 'Y', 'G', 'G', 'G', 'G', 'G', 'G', 'G' },
        { 'Y', 'Y', 'Y', 'Y', 'Y', 'Y', 'G', 'X', 'X', 'X' },
        { 'G', 'G', 'G', 'G', 'G', 'G', 'G', 'X', 'X', 'X' },
        { 'W', 'W', 'W', 'W', 'W', 'G', 'G', 'G', 'G', 'X' },
        { 'W', 'R', 'R', 'R', 'R', 'R', 'G', 'X', 'X', 'X' },
        { 'W', 'W', 'W', 'R', 'R', 'G', 'G', 'X', 'X', 'X' },
        { 'W', 'B', 'W', 'R', 'R', 'R', 'R', 'R', 'R', 'X' },
        { 'W', 'B', 'B', 'B', 'B', 'R', 'R', 'X', 'X', 'X' },
        { 'W', 'B', 'B', 'X', 'B', 'B', 'B', 'B', 'X', 'X' },
        { 'W', 'B', 'B', 'X', 'X', 'X', 'X', 'X', 'X', 'X' }
    };

    int x=3, y=9; 
    char replacement = 'C';  
    floodFill(mat, x, y, replacement); 

    for(int i=0; i<M; i++)
    {
        for(int j=0; j<N; j++)
            cout << setw(3) << mat[i][j];
        cout << "\n";
    }

    return 0;
}