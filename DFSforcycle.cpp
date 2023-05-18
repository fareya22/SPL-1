#include<stdio.h>
#include<stdlib.h>

void dfs_visit(int a,int b);

int graph[100][100];
char color[100];
int discovery_time[100];
int finishing_time[100];
int parent[100];
int path[100];
int times;

void dfs(int ver,int source)
{

     for(int i=1;i<=ver;i++)
        {
        color[i]='W';
        discovery_time[i]=INT_MAX;
        finishing_time[i]=INT_MAX;
        parent[i]=-1;
     }
     dfs_visit(ver,source);
     for(int i=1;i<=ver;i++)
     {
        if(color[i]=='W'){
            dfs_visit(ver,i);
        }
     }
     for(int i=1;i<=ver;i++)
     {
        printf("Parent of %d is: %d\n",i,parent[i]);
        printf("Discovery time of %d is: %d\n",i,discovery_time[i]);
        printf("Finishing time of %d is: %d\n",i,finishing_time[i]);
     }

}

void dfs_visit(int ver,int u)
{

    color[u]='G';
    times++;
    discovery_time[u]=times;

      for(int j=1;j<=ver;j++)
        {

         if(graph[u][j]==1 && color[j]=='W')
        {
            parent[j]=u;
            path[j]=path[u]+1;
            dfs_visit(ver,j);
         }
         else if(graph[u][j]==1 && color[j]=='G')
        {
           printf("cycle exist\n");
         }
      }
      color[u]='B';
      times++;
      finishing_time[u]=times;

}

int main()
{

    freopen("cycle.txt","r",stdin);

    int ver,p1,p2;
    printf("How many vertices are in your graph?\n");
    scanf("%d",&ver);

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

     dfs(ver,source);

     printf("Enter two nodes that you want to find shortest path:\n");
     scanf("%d %d",&p1,&p2);
     printf("Shortest path length= %d",abs(path[p1]-path[p2]));


}
