#include<stdio.h>
#include<stdlib.h>
#include<math.h> 

void print_array(int *arr, int n);
void counting_sort(int *arr, int B[], int n);
void radix_sort(int *arr, int n);

int main()
{
	int n, i; 
	
	
	printf("Enter the number of Integers: ");
	scanf("%d", &n);
	
	
	int *arr = (int *)malloc(n*sizeof(int));
	for(i=0; i<n; i++)
		scanf("%d", &arr[i]);
	/*
	n = 5; 
	int arr[] = {256, 780, 524, 625, 120};
	printf("Input taken ---------------------------------------\n");
	*/
	radix_sort(arr, n); 
	print_array(arr, n);

	return 0;
}

void print_array(int *arr, int n)
{
	for(int i=0; i<n; i++)
		printf("%d ", arr[i]);
	printf("\n");
}

void counting_sort(int *arr, int B[], int n)
{
	int count[10]; 
	for(int i=0; i<10; i++)
		count[i] = 0; 
		
	for(int i=0; i<n; i++)
		count[B[i]]++; 
		
	for(int i=1; i<10; i++)
		count[i] += count[i-1]; 
		
	int new_arr[n]; 
	for(int i=n-1; i>=0; i--)
	{
		new_arr[count[B[i]]-1] = arr[i]; 
		count[B[i]]--;
	}
	
	for(int i=0; i<n; i++)
		arr[i] = new_arr[i];
}

void radix_sort(int *arr, int n)
{
	int B[n];
	
	for(int i=1; i<=4; i++)
	{
		for(int j=0; j<n; j++)
		{
			int t = arr[j]; 
			int k=1;
			for(int m=0; m<i-1; m++)
				k = k*10;
				
			t = t/k;
			B[j] = t%10 ;
		}
		
		counting_sort(arr, B, n);
		/*
		printf("-------------------------------------------\n");
		print_array(arr, n);
		printf("-------------------------------------------\n");
		*/
	}
}
