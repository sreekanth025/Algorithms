#include<bits/stdc++.h>
using namespace std;

long long get_fibo(int n);

long long FIBO[100];
int main()
{
    FIBO[0] = 0;
    FIBO[1] = 1;
    for(int i=2; i<80; i++)
        FIBO[i] = -1; 

    bool flag = true; 
    int n;
    cout << "Enter a number between 0 and 79: (-1 to quit)\n"; 
    int count = 1;

    while(flag)
    {
        cout << "number " << count++ << ": "; 
        cin >> n; 

        if(n == -1)
        {
            cout << "Terminating Program...\n";
            return 0;
        }

        cout << "fibonacci of " << n << ": " << get_fibo(n) << "\n";
    }
    return 0;
}

long long get_fibo(int n)
{
    if(FIBO[n] == -1)
        FIBO[n] = get_fibo(n-1) + get_fibo(n-2);
    return FIBO[n];
}