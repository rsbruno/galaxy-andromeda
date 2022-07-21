#include <bits/stdc++.h>
#include <queue>
using namespace std;

#define V 9
int maxPath[3] = {-1};
queue<int> biggestParent;


void print_queue(queue<int> q)
{
    queue<int> temp = q;
    while (!temp.empty()) {
        cout << temp.front()<<" ";
        temp.pop();
    }
    cout << '\n';
}


int minDistance(int dist[], bool sptSet[])
{
    int min = INT_MAX, min_index;
    for (int i = 0; i < V; i++)
        if (sptSet[i] == false && dist[i] <= min)
            min = dist[i], min_index = i;
    return min_index;
}

void printPath(int parent[], int j)
{
    if (parent[j] == -1)
        return;
    printPath(parent, parent[j]);
    biggestParent.push(j);
}

void printSolution(int dist[], int n, int parent[], int src)
{
    int aux;
    for (int i = 0; i < V; i++)
    {
        if (dist[i] > maxPath[2])
        {
            queue<int> empty;
            swap(biggestParent, empty);
            maxPath[0] = src;
            maxPath[1] = i;
            maxPath[2] = dist[i];
            biggestParent.push(src);
            printPath(parent, i);
        }
        
    }
}

void dijkstra(int graph[V][V], int src)
{
    int dist[V];
    bool sptSet[V] = {false};
    int parent[V];

    for (int k = 0; k < V; k++)
        parent[k] = -1;

    for (int i = 0; i < V; i++)
        dist[i] = INT_MAX;

    dist[src] = 0;

    for (int count = 0; count < V; count++)
    {
        int u = minDistance(dist, sptSet);
        sptSet[u] = true;
        for (int v = 0; v < V; v++)
        {
            if (!sptSet[v] && graph[u][v] && dist[u] != INT_MAX && dist[u] + graph[u][v] < dist[v])
            {
                if (v == u)
                {
                    parent[v] = -1;
                }
                else
                {
                    parent[v] = u;
                }
                dist[v] = dist[u] + graph[u][v];
            }
        }
    }
    printSolution(dist, V, parent, src);
}

int main()
{
    int graph[V][V] = {{0, 4, 0, 0, 0, 0, 0, 8, 0},
                       {4, 0, 8, 0, 0, 0, 0, 11, 0},
                       {0, 8, 0, 7, 0, 4, 0, 0, 2},
                       {0, 0, 7, 0, 9, 14, 0, 0, 0},
                       {0, 0, 0, 9, 0, 10, 0, 0, 0},
                       {0, 0, 4, 0, 10, 0, 2, 0, 0},
                       {0, 0, 0, 14, 0, 2, 0, 1, 6},
                       {8, 11, 0, 0, 0, 0, 1, 0, 7},
                       {0, 0, 2, 0, 0, 0, 6, 7, 0}};
    for (int i = 0; i < V; i++)
    {
        dijkstra(graph, i);
    }

    cout << "Tavao: " << endl;
    print_queue(biggestParent);
    cout << maxPath[2] << endl;
    return 0;
}