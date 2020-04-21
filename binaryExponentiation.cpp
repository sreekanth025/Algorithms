#include<bits/stdc++.h>
using namespace std; 

#define int long long

// (a^b) % m
/*
int power(int a, int b, int m)
{
    if(b == 0)
        return 1;
    int res = power(a,  b/2, m);
    
    if(b%2)
        return ((res%m)*(res%m)*(a%m))%m;
    else return ((res%m)*(res%m))%m;
}
*/


int power(int x, unsigned int y, int p)  
{  
    int res = 1;
    x = x % p;
    if (x == 0) return 0; 
  
    while (y > 0)  
    {  
        if (y & 1)  
            res = (res*x) % p;  
  
        y = y>>1; 
        x = (x*x) % p;  
    }  
    return res;  
}  


int32_t main()
{
    int a, b, m;
    cout << "Enter a, b and m: ";
    cin >> a >> b >> m;

    int answer = power(a, b, m);
    cout << answer << "\n";
    return 0;
}
