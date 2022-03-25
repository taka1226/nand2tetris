#include<iostream>
#include<fstream>

using namespace std;

int main()
{
    ofstream outputfile;
    outputfile.open("test.txt");
    outputfile<<"test" << endl;
    outputfile<<"aaa" << endl;
    outputfile.close();
}
