#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>

using namespace std;

int main(void)
{
    ifstream myfile;
    ifstream myfile2;
    int maxLines = 0;

    myfile.open("att48.txt");
    if (myfile.is_open())
        while (myfile.peek() != EOF)
        {
            string line;
            getline(myfile, line);
            maxLines++;
        }

    int adjacencyMatrix[maxLines][maxLines];

    myfile2.open("att48.txt");
    if (myfile2.is_open())
    {
        string mychar, index, posX, posY;
        int indexLine = 0;
        while (myfile2)
        {
            int indexColumn = 0;
            myfile2 >> index;
            myfile2 >> posX;
            myfile2 >> posY;

            adjacencyMatrix[indexLine][indexColumn++] = stoi(index);
            adjacencyMatrix[indexLine][indexColumn++] = stoi(posX);
            adjacencyMatrix[indexLine++][indexColumn++] = stoi(posY);
        }
    }

    for (int i = 0; i < maxLines; i++)
    {
        cout << adjacencyMatrix[i][0] << ": " << adjacencyMatrix[i][1] << " " << adjacencyMatrix[i][2] << endl;
    }
}
