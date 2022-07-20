#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>

using namespace std;

vector<vector<int>> adjacencyMatrix;

int main(void)
{
    ifstream myfile;
    int maxLines = 0, size = 0;
    bool isFirstLine = true;

    myfile.open("att48.txt");
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
                {
                    row.resize(size);
                }
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
    }

    myfile.close();

    for (int i = 0; i < size; i++)
    {
        for (int j = 0; j < size; j++)
        {
            cout << adjacencyMatrix[i][j] << "\t";
        }
        cout << endl;
    }
}
