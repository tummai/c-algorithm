/*Tu Mai 
1001594173
Algorithm Hw2 Insertion sort a file ***/


#include <stdio.h>
#include <string.h>
#include<stdlib.h>
#define BUFSIZE 101


void displayArray (char *names[], int counter)
{
	int i;
	for (i=0;i<counter-1;i++)//print out to see if the value is store into array 
	{
		printf("%s",names[i]);
	}
	return;
}
void sort_by_length(char *names[],int counter)
{
	int step,i;
	char *temp;
	for(step = 0; step < counter - 1; step++)
	    for(i = 0; i < counter - step - 1; i++)
	    {
	        if(strlen(names[i]) > strlen(names[i+1]))
	        {
	            temp = names[i];
	            names[i] = names[i + 1];
	            names[i + 1] = temp;
	        }
	    }
}
void sort_by_strcmp(char *names[],int counter)
{
	int x, y;
   	char *temp;
	
	for (x = 0; x < counter-1; x++) 
    {
        for (y = x + 1; y < counter-1; y++)
        {
            if ((strcmp(names[x], names[y])) > 0) 
            {
                temp = names[x];
                names[x] = names[y];
                names[y] = temp;
			}
		}
	}
}
void sort_by_greater(char *names[],int counter)
{
	int x,y;
	char *temp;
	for (x = 0; x < counter-1; x++) 
    {
        for (y = x + 1; y < counter-1; y++)
        {
            if ((strcmp(names[y], names[x])) > 0) 
            {
                temp = names[y];
                names[y] = names[x];
                names[x] = temp;
			}
		}
	}
}
int main ( int argc, char *argv[])
{
	FILE *file;
	char inputfilename[BUFSIZE] = "";
	char buff[BUFSIZE];
	char ch;
	int i,j,step;
	//char *names[] = malloc(BUFSIZE*sizeof(char*));
	int counter = 0;
	
	printf("Enter file name: ");
	scanf("%s",inputfilename);
	
	//check name
	if(inputfilename == NULL)
	{
		printf("Cannot open file\n");
	}
	
	//open the input file
	file = fopen(inputfilename,"r");
	//check file
	if(file == NULL)
	{
		printf("There's an error openning input file\n");
		return -1;
	}
	int num_char = 0;
	//count to see how many lines
	while ((ch = fgetc(file)) != EOF)
	{
		num_char++;
		if(ch == '\n')
			counter++;
	}
	
	fclose(file);

	//char *arr[counter];
	char *names[counter];
	
	//open the input file
	file = fopen(inputfilename,"r");
	//check file
	if(file == NULL)
	{
		printf("There's an error openning input file\n");
		return -1;
	}
	else 
	{
		printf("\n\nData is loaded\n");
	}
	
	
	printf("Allocated space for sorting the data: %ld B (%d char and %d pointers)\n",num_char+(counter*sizeof(char*)),num_char,counter);
	printf("Pointer size: %ld Bytes\n\n", sizeof(char*));
	printf("Original Data: \n");
	counter = 0;
	
	
	
	while(fgets(buff,sizeof(buff)-1,file) != NULL)
	{
		names[counter] =(char*) malloc((strlen(buff)+1)*sizeof(char*));
		printf("%s",buff);//print out original data
		strcpy(names[counter],buff);
		counter++;
		
	}
	printf("\n\n");
	
	fclose(file);
	
	//sort by length
	printf("\n-------Sort by LENGTH ONLY --------\n");
	sort_by_length(names,counter);
	displayArray(names,counter);
	
	printf("\n-------Sort by strcmp--------\n");
	sort_by_strcmp(names,counter); 
	displayArray(names,counter);
	
	printf("\n-------Sort by Greater ------\n");
	sort_by_greater(names,counter);
	displayArray(names,counter);
	
	
	printf("\n-----Sort by length and lexicografic-----\n");
	/*for(k = 1; k< counter ; k++)
	{
		printf("hello");
		for(i = k+1; i < counter - k ; i++)
	    {
	        if(strlen(names[i]) > strlen(names[i+1]))
	        {
	            temp = names[i];
	            names[i] = names[i + 1];
	            names[i + 1] = temp;
	        }
	    }
		printf("hello");
	}
	char temp1[BUFSIZE];
	char temp2[BUFSIZE];
	for (i=1; i<counter; i++)
	{
		temp1[BUFSIZE] = *names[i];
		temp2[BUFSIZE] = *names[i+1];
		printf("hello");
		for (j=i+1;j=counter;j++)
		{
			if(temp1[j] > temp2[j]);
            	temp = names[i];
            	names[i] = names[i + 1];
            	names[i + 1] = temp;
		}
	}
	displayArray(names,counter);*/
	/*for (i = 0; i < counter - 1; i++)
	    {
	        for (j = i +1; j < counter - 1 ; ++j)
	        {
	            if ( (strlen(names[i]) > strlen(names[j])) && ((strcmp(names[i], names[j])) > 0) )
	            {
	                temp = names[i];
	                names[i] = names[j];
	                names[j] = temp;
	            }
	        }
	    }*/
	
	displayArray(names,counter);
	
	return 0;
}


