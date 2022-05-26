#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>

using namespace std;

int main(void)
{
    ifstream myfile;
    std::vector<std::string> out;

    myfile.open("att48.txt");
    if (myfile.is_open())
    {
        string mychar, index, posX, posY;
        while (myfile)
        {
            myfile >> index;
            myfile >> posX;
            myfile >> posY;
            cout << index << ": " << posX << " - " << posY << endl;
        }

        
    }
}