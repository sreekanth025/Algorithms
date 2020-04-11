#include<bits/stdc++.h>
using namespace std; 

int main()
{
    int test_cases; 
    cin >> test_cases; 

    for(int test=1; test <= test_cases; test++)
    {
        
        bool flag = true; 
        string output = ""; 

        int c_end = 0; 
        int j_end  = 0;

        int n; 
        cin >> n;

        int start, end; 

        vector<tuple<int, int, int> > times; 
        for(int i=0; i<n; i++)
        {
            cin >> start >> end; 
            times.push_back(make_tuple(start, end, i)); 
        }

        sort(times.begin(), times.end());

        for(int i=0; i<n; i++)
        {
            start = get<0>(times[i]);
            end = get<1>(times[i]);

            if(c_end <= start)
            {
                output.push_back('C'); 
                c_end = end;
            }

            else if(j_end <= start)
            {
                output.push_back('J');
                j_end = end;
            }

            else
            {
                flag = false; 
                break;
            }
        }


        cout << "Case #" << test << ": ";

        if(flag)
        {
            string final_output = "";

            vector<int> index; 
            for(int i=0; i<n; i++)
            {
                index.push_back(get<2>(times[i]));
            }

            for(int i=0; i<n; i++)
            {
                for(int j=0; j<n; j++)
                {
                    if(index[j] == i)
                        final_output.push_back(output[j]);
                }
            }

            cout << final_output << "\n"; 
        }
        else
        {
            cout << "IMPOSSIBLE\n";
        }
        
    }
    
    return 0;
}