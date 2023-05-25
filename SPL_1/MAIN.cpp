#include<bits/stdc++.h>
#include"makecfg.cpp"
using namespace std;

char color[100];
int discovery_time[100];
int finishing_time[100];
int parent[100];
int path[100];
int times;

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
void bfs(const vector<vector<int>>& matrix,int vertex,int source);
void print_final_DFS_list(const vector<vector<int>>& matrix,int vertex);

int main()

{
    cfg();
    analyze(mainStartLine+1, totalLine);
    edgeCreating(mainStartLine+1, totalLine);

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

    cout << "\t\t\tThe adjacency list representing the graph:\n";
    for (int i = mainStartLine; i <adjList.size(); ++i)
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

    cout << "\t\t\tThe adjacency matrix representing the graph:\n\n";
    for (int i = mainStartLine; i < maxNodes; ++i)
    {
        for (int j = mainStartLine; j < maxNodes; ++j)
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
    dfs(matrix,totalLine,mainStartLine+1);
    //print_final_DFS_list(matrix,totalLine);

    bfs(matrix,totalLine,mainStartLine+1);

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
    cout<<"\n\n\t\t\t\tDFS algorithm\n\n\n";
    for (int i = 1; i <= vertex; i++)
    {
        color[i] = 'W';
        discovery_time[i] = INT_MAX;
        finishing_time[i] = INT_MAX;
        parent[i] = -1;
    }

    int graph[100][100];
    for (int i = 0; i < vertex; i++)
    {
        for (int j = 0; j < vertex; j++)
        {
            graph[i][j] = matrix[i][j];
        }
    }
    /*  cout<<"\n\n\n";
      for (int i = 0; i < vertex; i++)
     {
         for (int j = 0; j < vertex; j++)
         {
             cout<<graph[i][j]<<" ";
         }
         cout<<"\n";
     }*/

    dfs_visit(graph, vertex, source);

    for(int i=1; i<=vertex; i++)
    {
        if(color[i]=='W')
        {
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
        else if(graph[newSource][j]==1 && color[j]=='G')
        {
            printf("cycle exist\n");
        }
    }
    color[newSource] = 'B';
    times++;
    finishing_time[newSource] = times;
    cout<<"THE color vector is";
    for(int i= 1; i<=vertex; i++)
    {
        cout<<" "<<color[i]<<" ";
    }
    cout<<endl;

}

void print_final_DFS_list(const vector<vector<int>>& matrix,int vertex)
{
    printf("Vertex     :");
    for(int i=1; i<=vertex; i++)
    {
        printf("%d\t",matrix[0][i]);

    }
    printf("\nColour     :");
    for(int i=1; i<=vertex; i++)
    {
        printf("%c\t",color[i]);
    }
    printf("\nParent     :");
    for(int i=1; i<=vertex; i++)
    {
        printf("%d\t",parent[i]);
    }
    printf("\n");
    printf("Finishing Time: ");
    for(int i=1; i<=vertex; i++)
    {
        printf("%d\t",finishing_time[i]);
    }
    printf("\n");
}

void bfs(const vector<vector<int>>& matrix, int vertex, int source)
{
    vector<char> color(vertex + 1, 'W');
    vector<int> parent(vertex + 1, -1);
    vector<int> distance(vertex + 1, 1000000);

    cout << "\n\n\t\t\t\tBFS algorithm\n\n\n";
    queue<int> q;

    color[source] = 'G';
    distance[source] = 0;
    q.push(source);

    while (!q.empty())
    {
        int v1 = q.front();
        q.pop();

        for (int v2 = 0; v2 < vertex; v2++)
        {
            if (matrix[v1][v2] == 1 && color[v2] == 'W')
            {
                color[v2] = 'G';
                q.push(v2);
                distance[v2] = distance[v1] + 1;
                parent[v2] = v1;
            }
        }

        color[v1] = 'B';
    }

    for (int i = mainStartLine; i < vertex; i++)
    {
        printf("Distance from source %d to %d is: %d\n", source, i, distance[i]);
        printf("Parent of %d is: %d\n", i, parent[i]);
    }
}
