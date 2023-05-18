#include<bits/stdc++.h>
using namespace std;

const int maximum=6;
int graph[100][100];
char color[100];

void bfs(int source)
{
    int parent[100];
    int distance[100];

       for(int i=1;i<maximum;i++)
        {
          color[i]='W';
          parent[i]=-1;
          distance[i]=INT_MAX;
       }
       int queue[maximum];
       int start = 0;
       int finish = 0;
       queue[finish] = source;
       finish++;
       color[source]='G';
       distance[source]=0;
       parent[source]=-1;
         while(finish-start>0)
            {
              int v1=queue[start];
               for(int i=1;i<maximum;i++)
               {
                  int v2=i;
                      if(graph[v1][v2]==1 && color[v2]=='W')
                      {
                        color[v2]='G';
                        queue[finish]=v2;
                        finish++;
                        distance[v2]=distance[v1]+1;
                        parent[v2]=v1;
                      }
               }
               queue[v1]='B';
               start++;
         }

      for(int i=1;i<maximum;i++)
    {
        printf("Distance from source %d to %d is: %d",source,i,distance[i]);
        printf("\nParent of %d is: %d\n",i,parent[i]);
      }



}

int main()
{

    freopen("bfs.txt","r",stdin);

    int edge,v1,v2;
    printf("How many edges are in your graph?\n");
    scanf("%d",&edge);

    for(int i=0;i<edge;i++){
        scanf("%d%d",&v1,&v2);
        graph[v1][v2]=1;
    }
    printf("Enter the source?\n");
    int source;
    scanf("%d",&source);
  //  printf("%d",graph[5][1]);

     bfs(source);

}
