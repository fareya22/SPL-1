#include<bits/stdc++.h>
using namespace std;

void dfs_visit(int a,int b);

int graph[100][100];
char color[100];
int discovery_time[100];
int finishing_time[100];
int parent[100];
int path[100];
int times;

void dfs(int vertex,int source)
{

     for(int i=1;i<=vertex;i++)
    {
        color[i]='W';
        discovery_time[i]=INT_MAX;
        finishing_time[i]=INT_MAX;
        parent[i]=-1;
     }

     dfs_visit(vertex,source);
     for(int i=1;i<=vertex;i++)
    {
        if(color[i]=='W')
        {
            dfs_visit(vertex,i);
        }
     }
     for(int i=1;i<=vertex;i++)
    {
        printf("Parent of %d is: %d\n",i,parent[i]);
        printf("Discovery time of %d is: %d\n",i,discovery_time[i]);
        printf("Finishing time of %d is: %d\n",i,finishing_time[i]);
     }

}

void dfs_visit(int vertex,int newSource)
{

    color[vertex]='G';
    times++;
    discovery_time[newSource]=times;

      for(int j=1;j<=vertex;j++)
        {

         if(graph[newSource][j]==1 && color[j]=='W')
        {
            parent[j]=newSource;
            path[j]=path[newSource]+1;
            dfs_visit(vertex,j);
         }
      }
      color[newSource]='B';
      times++;
      finishing_time[newSource]=times;

}

int main()
{

    freopen("dfsInput.txt","r",stdin);

    int vertex,p1,p2;
    printf("How many vertices are in your graph?\n");
    scanf("%d",&vertex);

    int edge,v1,v2;
    printf("How many edges are in your graph?\n");
    scanf("%d",&edge);

    for(int i=0;i<edge;i++)
    {
        scanf("%d%d",&v1,&v2);
        graph[v1][v2]=1;
    }
    printf("Enter the source?\n");

    int source;
    scanf("%d",&source);

     dfs(vertex,source);

     printf("Enter two nodes that you want to find shortest path:\n");
     scanf("%d %d",&p1,&p2);
     printf("Shortest path length= %d",abs(path[p1]-path[p2]));

}
