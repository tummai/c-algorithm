/*Tu Mai 
1001594173
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "edit_distance.h"

/*  Suggestions
- When you work with 2D arrays, be careful. Either manage the memory yourself, or
work with local 2D arrays. Note C99 allows parameters as array sizes as long as 
they are declared before the array in the parameter list. See: 
https://www.geeksforgeeks.org/pass-2d-array-parameter-c/
*/


int min(int v1, int v2, int v3)
{
    if(v1<=v2 && v1<=v3)
	{
        return v1;
    }
    if(v2<=v1 && v2<=v3)
	{
        return v2;
    }
    return v3;
}
void print_Table(char *second_string,char *first_string, int *array, int m, int n)
{
    
    int size_first=strlen(first_string);
    int size_second=strlen(second_string);
    printf("   |   |");
	int i, j, k;
	
    for( i=0; i<size_first; i++)
	{
        printf("  %c|", first_string[i]);
    }
    printf("\n--------");
	
    for(i=0; i<size_first; i++)
	{
        printf("----");
    }
    printf("\n");
	
    for(i=0; i<m; i++)
	{
        if(i==0)
		{
            printf("   |");
        }
		for(j=0; j<n; j++)
		{
			printf("%3d|", *((array+i*n)+j));
		}
			
        printf("\n--------");
		
    	for(k=0; k<size_first; k++)
		{
        	printf("----");
   	 	}
        printf("\n");
        printf("  %c|", second_string[i]);
    }
    
    
}

int edit_distance(char * first_string, char * second_string, int print_table)
{
    int i, j;
    int edit_DistanceTotal=-1;
    int arr[strlen(first_string)+1][strlen(second_string)+1];
	
	
    for(i=0; i<strlen(first_string)+1;i++)
	{
        for(j=0; j<strlen(second_string)+1;j++)
		{
            if(i==0 && j==0)
			{
                arr[i][j]=0;
			}
            else if(i==0)
			{
                arr[i][j]=arr[i][j-1]+1;
            }
            else if(j==0)
			{
                arr[i][j]=arr[i-1][j]+1;
            }
            else
			{
                if(first_string[i-1]==second_string[j-1])
				{
                    arr[i][j]=arr[i-1][j-1];
                }
                else
				{
                    arr[i][j]=1+min(arr[i][j-1],arr[i-1][j],arr[i-1][j-1]);
                }
            }
        }
    }
	
    if(print_table==1)
	{
        print_Table(first_string, second_string,(int *)arr, strlen(first_string)+1, strlen(second_string)+1);
    }
	return arr[strlen(first_string)][strlen(second_string)];
}


void spellcheck(char * dictname, char * testname)
{	
	
	    FILE *dictfile = fopen(dictname,"r");
		int max_length = 101;
		//char buff_test[max_length];
		//char buff_dict[max_length];
	    if (dictfile == NULL)
	    {
	        printf("Can't open file: %s\n",dictname);
	        exit(1);
	    }

	    FILE *testfile = fopen(testname,"r");
		if (testfile == NULL )

	    {
	        printf("Can't open file: %s \n",testname);
	        exit(1);
	    }

	    printf("Loading the dictionary file: %s\n", dictname);
	    printf("Loading the test file: %s\n",testname);
	    char testw[max_length];
		int con;
	    while(!feof(testfile))
	    {
	        int edit_dist;
	        fscanf(testfile,"%s",testw);
			//fgets(buff_test,max_length,testfile);
			
		        printf("\n------- Current test word: %s\n",testw);
		        char dictw[max_length];
		        int min_dist = 100;
		        rewind(dictfile);
		        while(!feof(dictfile))
		        {
		           fscanf(dictfile,"%s",dictw);
		           edit_dist = edit_distance(testw,dictw,0);
		           if(edit_dist < min_dist)
		           {
		               min_dist = edit_dist;
		           }
		        }
		        printf("Minimum distance: %d\n", min_dist);
		        printf("Words that give minimum distance: \n");
		        rewind(dictfile);
		        int n =0;
		        while(!feof(dictfile))
		        {
		           fscanf(dictfile,"%s",dictw);
				   //fgets(buff_dict,max_length,dictfile);
		           edit_dist = edit_distance(testw,dictw,0);
		           if(edit_dist == min_dist)
		           {
		               printf("%s\n",dictw);
		               n++;
				   }
		        }
		
   			        
			}
	    

	    fclose(testfile);
	    fclose(dictfile);

	
}


