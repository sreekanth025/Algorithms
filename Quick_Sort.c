#include <stdio.h>
#include<stdlib.h>

void swap(int *a, int *b)
{
    int t = *a;
    *a = *b;
    *b = t;
}

int partition(int arr[], int low, int high)
{
    int pivot = arr[high];
    int i = low-1;
    int j;
    for(j=low; j<high; j++)
    {
        if(arr[j] < pivot)
        {
            i++;
            swap(&arr[i], &arr[j]);
        }
    }
    swap(&arr[i+1], &arr[high]);
    return i+1;
}

void quickSort(int arr[], int low, int high)
{
    if(low < high)
    {
        int cp = partition(arr, low, high);
        quickSort(arr, low, cp-1);
        quickSort(arr, cp+1, high);
    }
}

int main()
{
    int n,i;
    scanf("%d", &n);
    int arr[n];
    for(i=0; i<n; i++)
        scanf("%d", &arr[i]);
        
    quickSort(arr, 0, n-1);
    for(i=0; i<n; i++)
        printf("%d\t", arr[i]);
    return 0;
}
