#include<bits/stdc++.h>
using namespace std; 

void subset_x(int arr[], int n, int k);
void iterate(int arr[], int bitmap[], int n, int k, int pSum, int x);
void printSubset(int arr[], int bitmap[], int n);
void printStatus(int arr[], int bitmap[], int n); 

bool present = false; 
int main()
{
    int n; 
    cout << "Number of elements in set: "; 
    cin >> n; 

    int arr[n]; 
    cout << "Enter the set elements: "; 
    for(int i=0; i<n; i++)
        cin >> arr[i]; 

    int x; 
    cout << "Enter the sum: "; 
    cin >> x; 

    subset_x(arr, n, x); 

    if(!present)
        cout << "There is no subset whose sum of elements is equal to given sum\n";
    return 0;
}

void subset_x(int arr[], int n, int x)
{
    int i;
    sort(arr, arr+n);

    int bitmap[n];
    for(i=0; i<n; i++)
        bitmap[i] = 0;

    while(arr[n-1] > x)
        n--; 
    int k = n;

    iterate(arr,bitmap, n, k, 0, x);
}

void iterate(int arr[], int bitmap[], int n, int k, int pSum, int x)
{
    for(int i=k-1; i>=0; i--)
    {
        if(pSum + arr[i] <= x)
        {
            bitmap[i] = 1; 
            pSum += arr[i];
        }
    }

    if(pSum == x)
    {
        present = true; 
        printSubset(arr, bitmap, n);
    }

    int j=0; 
    bool found = false; 
    while(j<n && !found)
    {
        if(bitmap[j] == 0 && bitmap[j+1] == 1)
            found = true; 
        else 
            j++;
    }

    if(!found)
        return ; 
    else
    {
        bitmap[j] = 1; 
        bitmap[j+1] = 0; 
        for(int i=j-1; i>=0; i--)
            bitmap[i] = 0;

        pSum = 0;
        for(int i=n-1; i >= j-1; i--)
        {
            if(bitmap[i] == 1)
                pSum += arr[i];
        }

        iterate(arr, bitmap, n, j, pSum, x); 
    }
    
}

void printSubset(int arr[], int bitmap[], int n)
{
    cout << "Subset: ";
    for(int i=0; i<n; i++)
    {
        if(bitmap[i] == 1)
            cout << arr[i]  << " "; 
    }
    cout << "\n";
}

void printStatus(int arr[], int bitmap[], int n)
{
    cout << "Current status ----------------------\n"; 
    for(int i=0; i<n; i++)
        printf("%3d ", arr[i]); 
    printf("\n");
    for(int i=0; i<n; i++)
        printf("%3d ", bitmap[i]);
    printf("\n");
    cout << "-------------------------------------\n";
}
