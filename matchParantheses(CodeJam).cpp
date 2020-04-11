#include<bits/stdc++.h>
using namespace std; 

int get_last_parantheses(string S);

int main()
{
    string S; 
    cin >> S; 

    int n = S.length(); 
    string S2 = ""; 
    
    for(int i=0; i<n; i++)
    {
        int num = S[i]-'0'; 
        int last_p = get_last_parantheses(S2);

        cout << "debug: num=" << num << " last paranthesis=" << last_p << "\n";

        if(last_p >= num)
        {
            string temp = to_string(num);
            S2.insert(S2.length()-num, temp); 

            cout << "debug: " << S2 << "\n";
        }
        else
        {
            int rem_p = num - last_p; 
            string str_num = to_string(num); 
            string temp = ""; 

            for(int t=0; t<rem_p; t++)
                temp.push_back('('); 

            temp.append(str_num); 

            for(int t=0; t<rem_p; t++)
                temp.push_back(')');

            S2.insert(S2.length()-last_p, temp); 
            
            cout << "debug: " << S2 << "\n";
        }
    }

    cout << S2 << "\n";

    return 0;
}

int get_last_parantheses(string S)
{
    int n = S.length(); 
    int count = 0;
    for(int i=n-1; i>=0; i--)
    {
        if(S[i] == ')')
            count++;
        else
        {
            break;
        }
    }
    return count;
}
