//
// Created by nikos on 4/9/2022.
//

#ifndef FILE_SYSTEM_WAD_H
#define FILE_SYSTEM_WAD_H

#import <iostream>
#import <fstream>
#include <algorithm>
#import <vector>
#import <queue>
using namespace std;

class Wad {
public:
    Wad(uint8_t* data);
    static Wad* loadWad(const string &path);
    string getMagic();
    bool isContent(const string &path);
    bool isDirectory(const string &path);
    int getSize(const string &path);
    int getContents(const string &path, char *buffer, int length, int offset = 0);
    int getDirectory(const string &path, vector<string> *directory);
private:
    struct TreeNode{
        string path;
        string name;
        int offset;
        int length;
        vector<TreeNode*> children;

        TreeNode(int _offset, int _length, string _name, string _path){
            offset = _offset;
            length = _length;
            name = _name;
            path = _path;
        }

        TreeNode(int _offset, int _length, string _name, string _path, vector<TreeNode*> _children){
            offset = _offset;
            length = _length;
            name = _name;
            path = _path;
            children = _children;
        }
    };
    TreeNode* root;
    string magic;
    uint8_t* wadData;
};


#endif //FILE_SYSTEM_WAD_H
