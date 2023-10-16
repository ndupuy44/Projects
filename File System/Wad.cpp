//
// Created by nikos on 4/9/2022.
//

#include "Wad.h"

Wad::Wad(uint8_t *data) {
    wadData = data;

    for(int i = 0; i < 4; i++){
        magic += data[i];
    }

    int numDescriptors = (data[4] | data[5] << 8 | data[6] << 16 | data[7] << 24);
    int offset = (data[8] | data[9] << 8 | data[10] << 16 | data[11] << 24);

    int currOffset, currLength, currLevel;
    TreeNode* currNode;
    string name;
    int treeLevel = 0;
    int mapCounter = 0;
    string dirPath = "/";
    root = new TreeNode(0, 0, "root", "/");

    for(int i = 0; i < numDescriptors; i++){
        currOffset = 0;
        currLength = 0;
        name = "";

        currOffset = (data[offset] | data[offset + 1] << 8 | data[offset + 2] << 16 | data[offset + 3] << 24);
        currLength = (data[offset + 4] | data[offset + 5] << 8 | data[offset + 6] << 16 | data[offset + 7] << 24);

        for(int j = 0; j < 8; j++){
            name += data[offset + 8 + j];
        }


        if(currLength == 0){
            if(name[0] == 'E' && isdigit(name[1]) && name[2] == 'M' && isdigit(name[3])){
                string dirName = name.substr(0, 4);
                dirPath += (dirName + "/");

                currLevel = 0;
                currNode = root;

                if(treeLevel == 0){
                    TreeNode* temp = new TreeNode(currOffset, currLength, dirName, dirPath);
                    currNode->children.push_back(temp);
                }
                else{
                    while(currLevel < treeLevel){
                        currNode = currNode->children[currNode->children.size() - 1];
                        currLevel++;
                    }
                    TreeNode* temp = new TreeNode(currOffset, currLength, dirName, dirPath);
                    currNode->children.push_back(temp);
                }
                mapCounter = 10;
                treeLevel++;
            }
            else if(name.find("_START") != string::npos){
                string dirName = name;
                dirName = dirName.substr(0, name.find("_START"));
                dirPath += (dirName + "/");

                currLevel = 0;
                currNode = root;

                if(treeLevel == 0){
                    TreeNode* temp = new TreeNode(currOffset, currLength, dirName, dirPath);
                    currNode->children.push_back(temp);
                }
                else{
                    while(currLevel < treeLevel){
                        currNode = currNode->children[currNode->children.size() - 1];
                        currLevel++;
                    }
                    TreeNode* temp = new TreeNode(currOffset, currLength, dirName, dirPath);
                    currNode->children.push_back(temp);
                }
                treeLevel++;
            }
            else {
                treeLevel--;
                string dirName = name;
                dirName = dirName.substr(0, name.find("_END"));
                dirPath.replace(dirPath.find(dirName), dirName.length() + 1, "");
            }
        }
        else if(mapCounter > 0){
            currLevel = 0;
            currNode = root;

            if(treeLevel == 0){
                TreeNode* temp = new TreeNode(currOffset, currLength, name, dirPath + name);
                currNode->children.push_back(temp);
            }
            else{
                while(currLevel < treeLevel){
                    currNode = currNode->children[currNode->children.size() - 1];
                    currLevel++;
                }
                TreeNode* temp = new TreeNode(currOffset, currLength, name, dirPath + name);
                currNode->children.push_back(temp);
            }

            mapCounter--;

            if (mapCounter == 0){
                treeLevel--;
                string dirName = dirPath.substr(dirPath.length() - 5);
                dirPath.replace(dirPath.find(dirName), dirName.length() , "");
            }
        }
        else{
            currLevel = 0;
            currNode = root;

            if(treeLevel == 0){
                TreeNode* temp = new TreeNode(currOffset, currLength, name, dirPath + name);
                currNode->children.push_back(temp);
            }
            else{
                while(currLevel < treeLevel){
                    currNode = currNode->children[currNode->children.size() - 1];
                    currLevel++;
                }
                TreeNode* temp = new TreeNode(currOffset, currLength, name, dirPath + name);
                currNode->children.push_back(temp);
            }
        }

        offset += 16;
    }
}

Wad * Wad::loadWad(const string &path) {
    ifstream file(path, ios::binary);
    file.seekg(0, ios::end);
    streamsize fileSize = file.tellg();
    file.seekg(0, ios::beg);
    uint8_t* data = new uint8_t[(int)fileSize];
    file.read((char*)data, fileSize);
    return new Wad(data);
}

string Wad::getMagic() {
    return magic;
}

bool Wad::isContent(const string &path) {
    queue<TreeNode*> q;
    q.push(root);

    while(!q.empty()){
        TreeNode* p = q.front();
        q.pop();

        string filePath = p->path;
        filePath.erase(remove(filePath.begin(),filePath.end(),'\0'), filePath.end());

        if(filePath.compare(path) == 0 && p->length != 0){
            return true;
        }

        for(int i = 0; i < p->children.size(); i++){
            q.push(p->children[i]);
        }
    }
    return false;
}

bool Wad::isDirectory(const string &path) {
    queue<TreeNode*> q;
    q.push(root);

    while(!q.empty()){
        TreeNode* p = q.front();
        q.pop();

        string filePath = p->path;
        filePath.erase(remove(filePath.begin(),filePath.end(),'\0'), filePath.end());

        if(filePath.substr(0, path.length()).compare(path) == 0 && p->length == 0){
            return true;
        }

        for(int i = 0; i < p->children.size(); i++){
            q.push(p->children[i]);
        }
    }
    return false;
}

int Wad::getSize(const string &path) {
    if(isDirectory(path)){
        return -1;
    }
    else{
        queue<TreeNode*> q;
        q.push(root);

        while(!q.empty()){
            TreeNode* p = q.front();
            q.pop();

            string filePath = p->path;
            filePath.erase(remove(filePath.begin(),filePath.end(),'\0'), filePath.end());

            if(filePath.compare(path) == 0){
                return p->length;
            }

            for(int i = 0; i < p->children.size(); i++){
                q.push(p->children[i]);
            }
        }
    }
    return -1;
}

int Wad::getContents(const string &path, char *buffer, int length, int offset) {
    if(isDirectory(path)){
        return -1;
    }
    else{
        queue<TreeNode*> q;
        q.push(root);

        while(!q.empty()){
            TreeNode* p = q.front();
            q.pop();

            string filePath = p->path;
            filePath.erase(remove(filePath.begin(),filePath.end(),'\0'), filePath.end());

            if(filePath.compare(path) == 0){
                if(p->length < length){
                    for(int i = 0; i < p->length; i++){
                        buffer[i] = wadData[p->offset + offset + i];
                    }
                    return p->length;
                }
                else{
                    for(int i = 0; i < length; i++){
                        buffer[i] = wadData[p->offset + offset + i];
                    }
                    return length;
                }
            }

            for(int i = 0; i < p->children.size(); i++){
                q.push(p->children[i]);
            }
        }
    }
    return -1;
}

int Wad::getDirectory(const string &path, vector<string> *directory) {
    if (isContent(path)){
        return -1;
    }
    else{
        queue<TreeNode*> q;
        q.push(root);

        while(!q.empty()){
            TreeNode* p = q.front();
            q.pop();

            string filePath = p->path;
            filePath.erase(remove(filePath.begin(),filePath.end(),'\0'), filePath.end());

            if(filePath.compare(path) == 0){
                for(int i = 0; i < p->children.size(); i++){
                    string name = p->children[i]->name;
                    name.erase(remove(name.begin(),name.end(),'\0'), name.end());
                    directory->push_back(name);
                }
                return p->children.size();
            }

            for(int i = 0; i < p->children.size(); i++){
                q.push(p->children[i]);
            }
        }
    }
    return -1;
}