#include<bits/stdc++.h>
using namespace std; 

int LCS(string A, string B, int m, int n);

int main()
{
    string A, B; 
    cout << "Enter two Strings:\n";
    cin >> A;
    cin >> B;

    cout << "Length of longest subsequence is: " << LCS(A, B, A.length(), B.length()) << "\n"; 
    return 0;
}

int LCS(string A, string B, int m, int n)
{
    if(m==0 || n==0)
        return 0; 
    
    if(A[m-1] == B[n-1])
        return 1 + LCS(A, B, m-1, n-1); 
    else
        return max(LCS(A, B, m-1, n), LCS(A, B, m, n-1)); 
} 