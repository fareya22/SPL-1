#include<bits/stdc++.h>
#include "cfg.h"

using namespace std;

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

//void make_graph()
int main()

{
    cfg();
    int graph[totalLine + 1][totalLine + 1];

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

    cout << "Before printing graph matrix" << endl;

  /* try{
    for (int i = 0; i < totalLine + 1; ++i)
    {
        for (int j = 0; j < totalLine + 1; ++j)
        {
            graph[i][j] = matrix[i][j];
        }
    }

    cout << "The graph matrix:\n";
    for (int i = 0; i < totalLine + 1; ++i)
    {
        for (int j = 0; j < totalLine + 1; ++j)
        {
            cout << graph[i][j] << " ";
        }
        cout << endl;
    }
   }catch(const exception& e)
   {
       cout << "Exception occurred: " << e.what() << endl;
   }*/
  cout << "After printing graph matrix" << endl;
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








