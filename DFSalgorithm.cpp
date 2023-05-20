#include<bits/stdc++.h>
#include <iostream>
#include <climits>
#include "cfg.h"
#include<stdlib.h>
//#define INT_MAX
using namespace std;

//void dfs_visit(int graph[][14], int vertex, int newSource);

char color[100];
int discovery_time[100];
int finishing_time[100];
int parent[100];
int path[100];
int times;
int distance[100];

struct Node
 {
    int data;
    Node* next;
    Node*previous;
};

Node* createNode(int data)
 {
   Node* newNode = new Node();
   newNode->data = data;
   newNode->next = nullptr;
   return newNode;
}

void addEdge(vector<Node*>& adjList, int src, int dest);
void createAdjacencyList(const vector<vector<int>>& matrix, vector<Node*>& adjList);
void dfs(const vector<vector<int>>& matrix, int vertex, int source);
void dfs_visit(int graph[][100], int vertex, int newSource);
void bfs(int graph[100][100],int source);

int main()

{
    cfg();
   // int graph[totalLine + 1][totalLine + 1];

    analyze(1, totalLine);
    edgeCreating(1, totalLine);

    int maxNodes = totalLine;
    //cout<<totalLine<<endl;
    //cout<<maxNodes<<endl;

    vector<vector<int>> matrix(maxNodes, vector<int>(maxNodes, 0));

    for (int i = 1; i <= maxNodes; ++i)
    {
        for (int j = 0; j < edge[i].size(); ++j)
        {
            int dest = edge[i][j];
            matrix[i - 1][dest - 1] = 1;
        }
    }

    vector<Node*> adjList;
    createAdjacencyList(matrix, adjList);

    cout << "The adjacency list representing the graph:\n";
    for (int i = 0; i < adjList.size(); ++i)
    {
        cout << i << "->";
        Node* currentNode = adjList[i];
        while (currentNode != nullptr)
        {
            cout << currentNode->data << " ";
            currentNode = currentNode->next;
        }
        cout << endl;
    }

    cout << "The adjacency matrix representing the graph:\n";
    for (int i = 0; i < maxNodes; ++i)
    {
        for (int j = 0; j < maxNodes; ++j)
        {
            cout << matrix[i][j] << " ";
        }
        cout << endl;
    }

    for (Node* node : adjList)
    {
        Node* current = node;
        while (current != nullptr)
        {
            Node* next = current->next;
            delete current;
            current = next;
        }
    }
dfs(matrix,totalLine,1);
//bfs(matrix,totalLine,1);

}

void addEdge(vector<Node*>& adjList, int src, int dest)
 {
  Node* newNode = createNode(dest);
  newNode->next = adjList[src];
  adjList[src] = newNode;
}


void createAdjacencyList(const vector<vector<int>>& matrix, vector<Node*>& adjList)
 {
    int numNodes = matrix.size();
     adjList.resize(numNodes, nullptr);

   for (int i = 0; i < numNodes; ++i)
    {
       for (int j = 0; j < numNodes; ++j)
        {
                 if (matrix[i][j] == 1)
                  {
                      addEdge(adjList, i+1, j+1);
                  }
       }
   }

}

void dfs(const vector<vector<int>>& matrix, int vertex, int source)
{
    for (int i = 1; i <= vertex; i++)
    {
        color[i] = 'W';
        discovery_time[i] = INT_MAX;
        finishing_time[i] = INT_MAX;
        parent[i] = -1;
    }

    // Convert 2D vector to 2D array
    int graph[100][100];
    for (int i = 0; i < vertex; i++)
    {
        for (int j = 0; j < vertex; j++)
        {
            graph[i][j] = matrix[i][j];
        }
    }
     cout<<"\n\n\n";
     for (int i = 0; i < vertex; i++)
    {
        for (int j = 0; j < vertex; j++)
        {
            cout<<graph[i][j]<<" ";
        }
        cout<<"\n";
    }

    dfs_visit(graph, vertex, source);

    for(int i=1;i<=vertex;i++){
        if(color[i]=='W'){
            dfs_visit(graph, vertex,i);
        }
     }

    for (int i = 1; i <= vertex; i++)
    {
        cout << "Parent of " << i << " is: " << parent[i] <<endl;
        cout << "Discovery time of " << i << " is: " << discovery_time[i] <<endl;
        cout << "Finishing time of " << i << " is: " << finishing_time[i] << endl;
    }
}

void dfs_visit(int graph[100][100], int vertex, int newSource)
{
    color[newSource] = 'G';
    times++;
    discovery_time[newSource] = times;

    for (int j = 1; j <= vertex; j++)
    {
        if (graph[newSource][j] == 1 && color[j] == 'W')
        {
            parent[j] = newSource;
            path[j] = path[newSource] + 1;
            dfs_visit(graph, vertex, j);
        }
    }
    color[newSource] = 'B';
    times++;
    finishing_time[newSource] = times;
}

void bfs(const vector<vector<int>>& matrix, int vertex,int source)
{


       for(int i=1;i<=vertex;i++)
        {
          color[i]='W';
          parent[i]=-1;
          distance[i]=INT_MAX;
       }
       int queue[totalLine],start=0,ending=0;
       queue[ending]=source;
       ending++;
       color[source]='G';
       distance[source]=0;
       parent[source]=-1;

    int graph[100][100];
    for (int i = 0; i < vertex; i++)
    {
        for (int j = 0; j < vertex; j++)
        {
            graph[i][j] = matrix[i][j];
        }
    }
         while(ending-start>0){
            int v1=queue[start];
               for(int i=1;i<totalLine;i++){
                  int v2=i;
                      if(graph[v1][v2]==1 && color[v2]=='W'){
                        color[v2]='G';
                        queue[ending]=v2;
                        ending++;
                        distance[v2]=distance[v1]+1;
                        parent[v2]=v1;
                      }
               }
               queue[v1]='B';
               start++;
         }

      for(int i=1;i<totalLine;i++){
        printf("Distance from source %d to %d is: %d",source,i,distance[i]);
        printf("\nParent of %d is: %d\n",i,parent[i]);
      }



}
