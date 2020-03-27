#include<bits/stdc++.h>
using namespace std; 

int main()
{
    int n, p; 
    cout << "Size of sequence: "; 
    cin >> n; 

    vector<int> a; 
    cout << "Sequence: "; 
    for(int i=0; i<n; i++)
    {   
        cin >> p;
        a.push_back(p);
    }
    
    vector <int> L(n, 1); 
    vector<int> P(n, -1); 

    for(int i=0; i<n; i++)
    {
        int max = L[0];
        bool flag = false; 
        int parent; 

        for(int j=0; j<i; j++)
        {
            if(L[j]+1 > max && a[i] > a[j])
            {
                max = L[j];
                parent = j; 
                flag = true; 
            }    
        }

        if(flag)
        {
            L[i] = 1 + max; 
            P[i] = parent;
            cout << "L[" << i << "] = " << L[i] << "\n";
        }
    }

    p = 0;
    for(int i=1; i<n; i++)
        if(L[i] > L[p])
            p = i; 
    cout << "Lenght of longest increasing subsequence: " << L[p] << "\n";

    stack<int> sequence; 
    while(p != -1)
    {
        sequence.push(a[p]);
        p = P[p];
    }
    while(!sequence.empty())
    {
        cout << sequence.top() << " "; 
        sequence.pop(); 
    }
}