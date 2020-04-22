/*Tu Mai 
1001594173
HWW5 - CSE 2320*/

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
//#define BUFSIZE 100

void printIndex(int idx)
{
	int i;
    for(i=0; i<idx; i++)
	{
		printf("\t%d, ", i );
	}
        
}
void printPar (int A[], int size, int first, int last)
{				
	int k;		
	for(k=0; k<size; k++)
	{
		if(k<=last && k>=first)
		{
			printf("\t%d,", A[k]);                    
		}	
		else 
		{			
			printf("\t,"); 			
		}
	}
}

void swap(int A[], int a, int b)
{           
	int temp;
	temp= A[a];
	A[a]= A[b];
	A[b]=temp;
	return;
}
void printArray(int array[], int size)
{
	int i;
	for(i =0; i< size; i++)
	{
		printf("\t%d,", array[i]);
	}
}
	
int medOfThree (int A[],int start, int end, int size)
{   
	int  j;
	int mid= floor(start+end)/2;  
	/*if (middle % 2 == 0)
	{
		middle = middle - 1;
	}*/
	
	int median;		
	if((A[end]>= A[start] && A[end]<= A[mid]) || (A[end]<= A[start] && A[end]>= A[mid]))
	{
		median=end;
	} 
	else if((A[start]>= A[mid] && A[start]<= A[end]) || (A[start]<= A[mid] && A[start]>= A[end]))
	{
		median= start;
	}
	else if((A[mid]>= A[start] && A[mid]<= A[end]) || (A[mid]>= A[end] && A[mid]<= A[start]))
	{
		median = mid;
	}
			
	printf("\nStart of Partition(A, N, %d, %d)\n",start, end);
	printPar(A, size, start, end);
	printf("\tA[%d]=%d, A[%d] = %d, A[%d] = %d\n", start, A[start], median, A[median], end, A[end]);
		
	swap(A, median, end);  

	int pivot= A[end];  
	int t= start;
	printPar(A, size, start, end);
	printf("<- updated pivot: %d", pivot);
	for(j=start; j<=end-1; j++)
	{
		if(A[j] <= pivot)
		{				
			swap(A, j, t); 		
			t++;
			}
		}
	swap(A,t, end);		
	printf("\n");
	printPar(A,size,start,end);
	printf(" <- Partitioned array aorund %d, at the final index %d\n", pivot, mid);
	printf(" end of partiton (A, N, %d, %d)", start, end);
	return t;
}
		
void medianqSort(int Arr[], int start, int end, int size)
{		
	if(start >=end) 
	{
		return;
	}
	int pIndex = medOfThree(Arr, start, end, size);
	medianqSort(Arr, start, pIndex-1, size);
	medianqSort(Arr, pIndex+1,end, size);
}

int main () 
{
	FILE *fp;
	//int buff[BUFSIZE];
	int n=1,k;					
	int *array;					
	
	fp= fopen("data1.txt","r");		
	while(n > 0 && !feof(fp))
	{			
										
		fscanf(fp, "%d", &n);				
		if(n<=0)
		{
			break;
		}
		array = (int*)malloc(n*sizeof(int)); 
				
		for( k=0;k<n; k++)
		{						
			fscanf(fp, "%d", &array[k]);		
		}
		printf("\nLoaded new array:\n");
		printf("\nIndexes:\n");

		//int k;
		printIndex(n);
		
		printf("\nOriginal array: \n");
		printArray(array, n);
		
		medianqSort(array, 0, n-1,n);		

		printf("\nSorted array: \n");
		printArray(array, n);
		printf("\n\n");

		free(array);
	}

	fclose(fp);	
	return 0;
}