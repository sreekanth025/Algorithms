#include<bits/stdc++.h>
using namespace std; 

int rodCut(vector<int> price);

int main()
{
    int n, p; 
    cout << "Length of rod: "; 
    cin >> n; 

    vector<int> price; 
    cout << "Prices: ";
    for(int i=0; i<n; i++)
    {
        cin >> p;
        price.push_back(p);
    }

    cout << "Maximum profit: " << rodCut(price) << "\n"; 
    return 0;
}

int rodCut(vector<int> price)
{
    int n = price.size();
    int i, j, T[n+1]; 

    T[0] = 0; 
    for(i=1; i<=n; i++)
    {
        T[i] = 0; 
        for(j=0; j<i; j++)
            T[i] = max(T[i], price[j] + T[i-j-1]); 
    }

    return T[n];
}