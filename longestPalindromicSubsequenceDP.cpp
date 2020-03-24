#include<bits/stdc++.h>
using namespace std;

int LPS(string A);

int main()
{
    string A;
    cout << "Enter the string: ";
    cin >> A;

    cout << "Length of longest palindromic subsequence: " << LPS(A);
    return 0;
}

int LPS(string A)
{
    int m = A.length();
    int i, j, k, L[m][m]; 

    for(i=0; i<m; i++)
        L[i][i] = 1;
    
    for(j=1; j<m; j++)
    {
        for(i=0; i<m-j; i++)
        {
            if(A[i] == A[i+j])
            {
                if(i+1 <= i+j-1) 
                    L[i][i+j] = 2 + L[i+1][i+j-1];
                else 
                    L[i][i+j] = 2;
            }
            else
            {
                int a = L[i][i+j-1];
                int b = L[i+1][i+j];
                L[i][i+j] = (a > b)? a : b;
            }
            
        }
    }

    return L[0][m-1];
}