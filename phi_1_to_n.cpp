/*
Totient of all numbers between 1 and n.
Time Complexity: O(n.lg(lg(n)))
*/

#include<bits/stdc++.h>
using namespace std; 

vector<int> phi_1_to_n(int n)
{
    vector<int> phi(n+1);

    phi[0] = 0;
    phi[1] = 1;
    for(int i=2; i<=n; i++)
        phi[i] = i; 
    
    for(int i=2; i<=n; i++)
    {
        if(phi[i] == i)
        {
            for(int j=i; j<=n; j += i)
                phi[j] -= phi[j]/i; 
        }
    }

    return phi;
}

int main()
{
    int n;
    cout << "n: ";
    cin >> n;

    vector<int> phi = phi_1_to_n(n);
    for(int i=0; i<phi.size(); i++)
        cout << setw(3) << i <<  ": " << phi[i] << "\n";
    return 0;
}