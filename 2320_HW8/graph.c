/* TU MAI 
1001594173 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define SIZE 100


struct graph
{

    int vertex_no;
    int ** adjmatx;
	//int ** weightmatrix;

}typedef graph;

struct str
{

    char name[SIZE];

}typedef str;

graph *createGraph(int num)
{
    int i,j;
    graph *g = malloc(sizeof(graph));
    g->vertex_no = num;
    g->adjmatx = (int**)calloc(num,sizeof(int*));

    for(i = 0; i < num; i++)
    {
        g->adjmatx[i] = calloc(num,sizeof(int));
    }

    return g;
}

void deleteGraph(graph *g)
{
    int i;
    for(i = 0; i < g->vertex_no; i++)
    {
        free(g->adjmatx[i]);
    }
    free(g->adjmatx);
    free(g);
}

void DFS_visit(graph *g,str *names,str *color, int t, int *pred,int *conn, int lable)
{

    strcpy(color[t].name,"GRAY");
    int i;
    conn[t] = lable;
    for(i = 0; i < g->vertex_no; i++)
    {
        if(g->adjmatx[t][i] == 1)
        {
            if(strcmp(color[i].name,"WHITE") == 0)
            {
                pred[i] = t;
                DFS_visit(g,names,color,i,pred,conn,lable);
            }
        }
    }


    strcpy(color[t].name,"BLACK");

}



int max(int *arr,int size)
{
    int max = arr[0];
    int i;
    for(i = 1; i < size; i++)
    {
        if(max < arr[i])
            max = arr[i];
    }
	
    return max;
}

void DFS(graph *g, str *names, int *conn)
{
	int i;
	str color[g->vertex_no]; 
	int pred[g->vertex_no]; 
	
	for(i = 0; i < g->vertex_no; i++)
	{
        strcpy(color[i].name,"WHITE");
        pred[i] = -1;
		
	}

    int group_count = 0;
       for(i = 0; i < g->vertex_no; i++)
        {
            if(strcmp(color[i].name,"WHITE") == 0)
            {
                int lable = group_count + 1;
				//printf("Aaaaaaa");
                DFS_visit(g,names,color,i,pred,conn, lable);
				//printf("DUMAAAAAAA");
                group_count++;
            }

        }
}




int min(int distance[], str *color, int N)
{
	int min= 999;
	int min_index, i;
	for(i=0; i<N; i++)
	{
		if(strcmp(color[i].name, "WHITE")==0 && distance[i]<min)
		{
			min=distance[i];
			min_index=i;
		}
	}
	return min_index;
}

void printMST(int pred[], int distance[], int N)
{
	int t, totalmst=0;
	printf("\nRunning MST_prim...\nMST tree edges:\n");
   	for ( t = 0; t < N; t++)
	{
		if(distance[t]!=999)
		{
      		printf("(%3d,%3d,%3d)\n", pred[t], t, distance[t]); 
   		}
		totalmst+=distance[t];
 	}
	printf("total MST cost: %d\n\nFinished MST_prim.\n",totalmst); 
	return;
}

void prim(graph *g, graph* weights,int startVertex ,int N)
{
	int i, j,v, p,minVertex, minVal, totalmst=0;
	int distance[N];
	int pd[N];
	str color[N];
	for(p=0;p<N;p++)
	{		
		distance[p]=999; 
		strcpy(color[p].name,"WHITE");	
		
	} 

	distance[startVertex]=0;					
	pd[startVertex]=-1;

	for(i=1;i<N;i++){		
		minVal= min(distance, color, N);
		strcpy(color[minVal].name,"GREY");
		for(j=0;j<N;j++)
		{			
			if((g->adjmatx[minVal][j]==1) && (strcmp(color[j].name, "WHITE")==0) && (weights->adjmatx[minVal][j]<distance[j]))
			{    
				pd[j]=minVal;
				distance[j]= weights->adjmatx[minVal][j];
				
			}
		} 
		
		if(strcmp(color[minVal].name,"GREY")==0 && weights->adjmatx[minVal][i]<distance[i])
		{
		}
	}
	

	printMST(pd, distance, N); 
	return;
}





int indexof(char *name, str *arr, int size)
{
    int i;
    for(i = 0; i < size; i++)
    {
        if(strcmp(name,arr[i].name) == 0)
            return i;

    }
    return -1;
}

int main()
{
	int N,i,j, Weighted, startVertex; //where N is number of vertices


	printf("Is it a weighted graph: ");
	scanf("%d",&Weighted);
	printf("%d -yes (edges have weights), else-no)?: ", Weighted);
	printf("Enter starting vertex for MST:");
	scanf("%d",&startVertex); 
	printf("\nGiven starting vertex for MST was: %d\n", startVertex);
	printf("Enter number of vertices, N: ");
	scanf("%d",&N);
	//printf("%d\n",N);
	printf("\nweightsOn = %d\n",Weighted);

    str names[N];

    graph *g = createGraph(N);
	graph *w = createGraph(N);

    for(i = 0; i < N; i++)
    {

        printf("Enter name1: ");
        scanf("%s",names[i].name);

    }
    while(1)
    {
        str name1;
        str name2;
		str weight;
        printf("Enter name1 name2 (weight if applicable):______");
		if (Weighted == 1)
		{
			scanf("%s %s %s",name1.name,name2.name,weight.name);
	        if(strcmp(name1.name, "-1") == 0 || strcmp(name2.name, "-1") == 0 || strcmp(weight.name,"-1") == 0)
	        {
				printf("Invalid v1 or v2\n");
	            break;
	        }
			
		}
		else
		{
			scanf("%s %s",name1.name,name2.name);
	        if(strcmp(name1.name, "-1") == 0 || strcmp(name2.name, "-1") == 0)
	        {
				printf("Invalid v1 or v2");
	            break;
	        }
		}
        
   		//printf("TEST0");
        int check1  = indexof(name1.name, names,N);
        int check2 = indexof(name2.name, names,N);
		//printf("TEST1");
        if(check1 != -1 || check2 != -1)
        {
            g -> adjmatx[check1][check2] = 1;
            g-> adjmatx[check2][check1] = 1;
			if (Weighted == 1)
			{
					//printf("TEST2");
				w -> adjmatx[check2][check1] = atoi(weight.name);
				w -> adjmatx[check1][check2] = atoi(weight.name);
					//printf("TEST3");
			}
			
        }
		else 
		{
			if (Weighted == 1)
			{
				w->adjmatx[check1][check2] = 0;
				w->adjmatx[check2][check1] = 0;
			}
		}
			

    }
    printf("\n\nGRAPH:\n");
	printf("weighted = %d\n", Weighted);
	printf("N = %d", N);
	printf("\n");
    for(i = 0; i < N; i++)
    {
        printf("%d-%s\n", i, names[i].name);
    }
    printf("\n");
    
	
    printf("\nEdges 2D matrix: \n");
    printf("   |");
    for(i = 0; i < N; i++)
    {
        printf("%d   ", i);
    }
    printf("\n");
    printf("\n");
    for(i = 0; i < N; i++)
    {
        printf(" %d |", i);
        for(j = 0; j < N; j++)
        {

            printf("%d   ",g -> adjmatx[i][j]);
        }
        printf("\n");

    }
	if (Weighted == 1)
	{
		printf("\nWeight 2D matrix:\n\n");
	    printf("   |");
	    for(i = 0; i < N; i++)
	    {
	        printf("%-4d", i);
	    }
	    printf("\n");
	    printf("\n");
	    for(i = 0; i < N; i++)
	    {
	        printf(" %-d |", i);
	        for(j = 0; j < N; j++)
	        {
				
				printf("%-4d",w -> adjmatx[i][j]);
					
	        }
			
	        printf("\n");
		}
		
		
	}
    int conn[g -> vertex_no];
    for(i = 0; i < g -> vertex_no; i++)
    {
        conn[i] = 0;
    }
	
	//printf("TEST");
	printf("\n\nRunning DFS...\n");
    DFS(g, names, conn);
	printf("Finished DFS\n\n");
	
	
	
    int no_group = max(conn,g -> vertex_no);
    printf("\nNumber of groups: %d\n",no_group);

    for(i = 1; i <= no_group; i++)
    {
        printf("\nGroup: %d\n", i);
        for(j = 0; j < g -> vertex_no; j++)
        {
            if(i == conn[j])
            {
                printf("%s\n",names[j].name);
            }
        }
    }
	if ( Weighted == 1)
	{

		prim(g, w,startVertex,g->vertex_no);
	}
	else 
	{
		printf("\nThis is not a weighted graph. We will not run MST_Prim for it.\n");
	}
	
	
    deleteGraph(g);
	deleteGraph(w);
	
	
	
    return 0;
}

