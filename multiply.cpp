/*
Multiply two numbers a and b modulo m. 
a and b fit in the built-in data types, 
but their product is too big to fit in a 64-bit integer.
*/

#include<bits/stdc++.h>
using namespace std;
#define int long long

// Time Complexity: O(lg b).
int multiply(int a, int b, int m)
{
    if(a == 0)
        return 0;
    
    if(a%2)
        return ((2*(multiply(a/2, b, m)%m))%m + b)%m; 
    else
        return (2*(multiply(a/2, b, m)%m))%m;
}

int32_t main()
{
    int a, b, m;
    cin >> a >> b >> m ;

    int answer = multiply(a, b, m); 
    cout << answer << "\n";
    return 0;
}