// number of ways to write N as the sum of 1, 3, and 4.

#include<bits/stdc++.h>
using namespace std; 

int main()
{
    int n; 
    cout << "Enter the number: "; 
    cin >> n; 

    int ways[n+1]; 
    ways[0] = ways[1] = ways[2] = 1;
    ways[3] = 2;                        //3 =  3 and 1+1+1  

    for(int i=4; i<=n; i++)
    {
        ways[i] = ways[i-1] + ways[i-3] + ways[i-4];
    }

    cout << "Number of ways: " << ways[n] << "\n";
    return 0;
}