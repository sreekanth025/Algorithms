#include<bits/stdc++.h>
using namespace std; 

int LCS(string A, string B);

int main()
{
    string A, B; 
    cout << "Enter two Strings:\n";
    cin >> A;
    cin >> B;

    cout << "Length of longest subsequence is: " << LCS(A, B) << "\n"; 
    return 0;
}

int LCS(string A, string B)
{
    int m = A.length();
    int n = B.length();

    int Length[m+1][n+1]; 

    for(int i=0; i<=m; i++)
    {
        for(int j=0; j<=n; j++)
        {
            if(i==0 || j==0)
                Length[i][j] = 0;  
            
            else if(A[i-1] == B[j-1])
                Length[i][j] = 1 + Length[i-1][j-1];

            else
                Length[i][j] = max(Length[i-1][j], Length[i][j-1]); 
        }
    }

    return Length[m][n];
} 