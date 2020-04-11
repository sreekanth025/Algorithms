/*
List of all primes upto an integer n.
Time Complexity: O(n).
*/

#include<bits/stdc++.h>
using namespace std;

vector<int> getPrimes(int n)
{
    const int N = n;
    vector<int>lp(N+1, 0); // stores the minimum prime factor for every integer in [2, N].

    vector<int> pr;
    for(int i=2; i<=N; i++)
    {
        if(lp[i] == 0)
        {
            lp[i]  = i;
            pr.push_back(i);
        }
        for(int j=0; j<(int)pr.size() && pr[j]<=lp[i] && i*pr[j]<=N; j++)
            lp[i*pr[j]] = pr[j];
    }
    return pr;
}

int main()
{
    int n;
    cout << "n: ";
    cin >>  n;

    vector<int> primes = getPrimes(n);
    
    cout << "Primes: \n"; 
    for(auto it = primes.begin(); it != primes.end(); it++)
        cout << (*it) << " ";
    cout << "\n";
    
    return 0;
}