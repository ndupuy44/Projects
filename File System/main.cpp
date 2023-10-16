#include <iostream>
#include "Wad.h"
using namespace std;
void exploreDirectory(Wad *data, const string path, int level)
{
    for (int index = 0; index < level; index++)
        cout << " ";
    vector<string> entries;
    cout << "[Objects at this level:" << data->getDirectory(path, &entries) << "]"
         << endl;
    for (string entry : entries)
    {
        string entryPath = path + entry;
        for (int index = 0; index < level; index++)
            cout << " ";
        if (data->isDirectory(entryPath))
        {
            cout << level << ". DIR: " << entry << endl;
            exploreDirectory(data, entryPath + "/", level + 1);
        }
        else if (data->isContent(entryPath))
            cout << level << ". CONTENT: " << entry << "; Size: " << data->getSize(entryPath) << endl;
        else
            cout << "***WARNING: entry " << entry << " has invalid type!***" << endl;
    }
}
void exploreDirectory(Wad *data, const string path)
{
    cout << "EXPLORING: " << path << endl;
    exploreDirectory(data, path, 1);
}
int main()
{
    Wad *myWad = Wad::loadWad("sample1.wad");
    //exploreDirectory(myWad, "/");
    string path = "/E1M0/01.txt";
    char buffer[17];
    myWad->getContents(path, buffer, 15);
    cout << buffer;
}