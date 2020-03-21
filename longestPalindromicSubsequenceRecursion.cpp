#include<bits/stdc++.h>
using namespace std;

int LPS(string A, int i, int j);

int main()
{
    string A;
    cout << "Enter the string: ";
    cin >> A;

    cout << "Length of longest palindromic subsequence: " << LPS(A, 0, A.length()-1);
    return 0;
}

int LPS(string A, int i, int j)
{
    if(i==j)
        return 1; 
    if(A[i]==A[j] && i+1 == j)
        return 2; 

    if(A[i] == A[j])
        return  2 + LPS(A, i+1, j-1);  
    
    return max(LPS(A, i+1, j), LPS(A, i, j-1));
}