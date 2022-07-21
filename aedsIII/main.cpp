#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <bits/stdc++.h>
#include <queue>

using namespace std;

vector<vector<int>> adjacencyMatrix;

//#define V 9
int size = 0;
int maxPath[3] = {-1};
queue<int> biggestParent;

void showOutputFormated(queue<int> q)
{
    queue<int> temp = q;
    while (!temp.empty())
    {
        cout << temp.front() << " ";
        temp.pop();
    }
    cout << '\n';
}

int minDistance(int dist[], bool sptSet[])
{
    int min = INT_MAX, min_index;
    for (int i = 0; i < size; i++)
        if (sptSet[i] == false && dist[i] <= min)
            min = dist[i], min_index = i;
    return min_index;
}

void mountPath(int parent[], int j)
{
    if (parent[j] == -1)
        return;
    mountPath(parent, parent[j]);
    biggestParent.push(j);
}

void mountSolution(int dist[], int n, int parent[], int src)
{
    int aux;
    for (int i = 0; i < size; i++)
        if (dist[i] > maxPath[2])
        {
            queue<int> empty;
            swap(biggestParent, empty);
            maxPath[0] = src;
            maxPath[1] = i;
            maxPath[2] = dist[i];
            biggestParent.push(src);
            mountPath(parent, i);
        }
}

void dijkstra(int src)
{
    int dist[size];
    bool sptSet[size] = {false};
    int parent[size];
    for (int k = 0; k < size; k++)
        parent[k] = -1;
    for (int i = 0; i < size; i++)
        dist[i] = INT_MAX;
    dist[src] = 0;
    for (int count = 0; count < size; count++)
    {
        int u = minDistance(dist, sptSet);
        sptSet[u] = true;
        for (int v = 0; v < size; v++)
            if (!sptSet[v] && adjacencyMatrix[u][v] && dist[u] != INT_MAX && dist[u] + adjacencyMatrix[u][v] < dist[v])
            {
                if (v == u)
                    parent[v] = -1;
                else
                    parent[v] = u;
                dist[v] = dist[u] + adjacencyMatrix[u][v];
            }
    }
    mountSolution(dist, size, parent, src);
}

int main(void)
{
    ifstream myfile;
    bool isFirstLine = true;
    vector<string> instances = {"n25.txt", "n50.txt", "n100.txt", "n250.txt", "n500.txt", "n750.txt", "n1000.txt"};

    for (auto &instance : instances)
    {
        myfile.open("./instances/" + instance);
        if (myfile.good())
        {
            while (myfile)
            {
                if (isFirstLine)
                {
                    string sLine;
                    getline(myfile, sLine);
                    size = stoi(sLine);
                    adjacencyMatrix.resize(size);
                    for (auto &row : adjacencyMatrix)
                        row.resize(size);
                    isFirstLine = false;
                }
                else
                {
                    int posX, posY, weight;
                    int indexColumn = 0;
                    myfile >> posX;
                    myfile >> posY;
                    myfile >> weight;
                    adjacencyMatrix[posX][posY] = weight;
                    adjacencyMatrix[posY][posX] = weight;
                }
            }
            for (int i = 0; i < size; i++)
                dijkstra(i);
            cout << instance << endl;
            showOutputFormated(biggestParent);
            cout << maxPath[2] << endl;
        }
        cout << endl;
        isFirstLine = true;
        vector<vector<int>> empty;
        swap(adjacencyMatrix, empty);
        for (int i = 0; i < 3; i++)
            maxPath[i] = -1;
        myfile.close();
    }
}
