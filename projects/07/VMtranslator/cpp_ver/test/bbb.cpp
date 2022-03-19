#include <iostream>
#include <fstream>

using namespace std;

class xyz
{
  public:
    int x;
};

int main()
{
    xyz a;
    a.x = 45; // replace by 45 or 78 it works. Replace by 13, 26 it shows garbage values.

    ifstream of;
    of.open("example.txt");
    string line;
    getline(of, line);
    of.close();
    return 0;

}
