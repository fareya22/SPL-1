#include<bits/stdc++.h>
#include "makecfg.cpp"
using namespace std;

int g[100][100];

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



void make_graph()
{
               cfg();

  /* int mat[100][100];

      for(int i=0;i<=totalLine;i++){
        for(int j=0;j<=totalLine;j++){
            mat[i][j]=0;
        }
      }

      for ( int i = 1; i <= totalLine; ++i )
      {
        int a=edge[i][0];
       // cout<<a<<"\n";
        int b=edge[i][1];
      //  cout<<b<<"\n";

        mat[a][b]=1;
      }

   /*   for(int i=1;i<=totalLine;i++){
        for(int j=0;j<=totalLine;j++){
            if(mat[i][j]!=0)cout<<mat[i][j]<<" ";
        }
        cout<<"\n";
      }*/

  analyze(1, totalLine);
  edgeCreating(1, totalLine);

  int maxNodes = totalLine;
  vector<vector<int>> matrix(maxNodes, vector<int>(maxNodes, 0));

  for (int i = 1; i <= maxNodes; ++i)
    {
       for (int j = 0; j < edge[i].size(); ++j)
    {
          int dest = edge[i][j];
           matrix[i - 1][dest - 1] = 1;
    }
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

  for(int i=0;i<=totalLine;i++)
    {
        for(int j=0;j<=totalLine;j++)
        {
            g[i][j]=matrix[i][j];
        }
    }

  vector<Node*> adjList;
  createAdjacencyList(matrix, adjList);

  cout << "The adjacency list representing the graph:\n";
  for (int i = 0; i < adjList.size(); ++i)
    {
       cout << i << ": ";
        Node* currentNode = adjList[i];
       while (currentNode != nullptr)
           {
                cout << currentNode->data << " ";
                 currentNode = currentNode->next;
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

}









