#include <iostream>
#include <vector>
#include <map>
#include <algorithm>
using namespace std;

struct Node{
    string name;
    long gatorID;
    int height;
    Node* left = nullptr;
    Node* right = nullptr;
    Node(string _name, long _gatorID){
        name = _name;
        gatorID = _gatorID;
        height = 1;
    }
};

int getHeight(Node* node){
    if(node == nullptr){
        return 0;
    }
    return node->height;
}

int getBalanceFactor(Node* node){
    if(node == nullptr){
        return 0;
    }
    return (getHeight(node->left) - getHeight(node->right));
}

Node* rotateLeft(Node *node)
{
    Node* child = node->right;
    Node* grandchild = node->right->left;
    child->left = node;
    node->right = grandchild;
    return child;
}

Node* rotateRight(Node *node)
{
    Node* child = node->left;
    Node* grandchild = node->left->right;
    child->right = node;
    node->left = grandchild;
    return child;
}

Node* getInorderSuccessor(Node* node){
    if(node->left == nullptr){
        return node;
    }
    else{
        return getInorderSuccessor(node->left);
    }
}

bool checkName(string name){
    int count = 0;
    for(int i = 0; i < name.size(); i++){
        if(isalpha(name[i])){
            count++;
        }
    }
    if(count == name.size()){
        return true;
    }
    else{
        return false;
    }
}

bool checkID(string gatorID){
    if(gatorID.size() != 8){
        return false;
    }
    int count = 0;
    for(int i = 0; i < gatorID.size(); i++){
        if(isdigit(gatorID[i])){
            count++;
        }
    }
    if(count == gatorID.size()){
        return true;
    }
    else{
        return false;
    }
}

Node* insert(Node* root, long gatorID, string name){
    if(root == nullptr){
        cout << "successful" << endl;
        return (new Node(name, gatorID));
    }
    else if(gatorID < root->gatorID){
        root->left = insert(root->left, gatorID, name);
    }
    else if(gatorID > root->gatorID){
        root->right = insert(root->right, gatorID, name);
    }
    else if(root->gatorID == gatorID){
        cout << "unsuccessful" << endl;
        return root;
    }

    root->height = max(getHeight(root->left),getHeight(root->right)) + 1;
    int balanceFactor = getBalanceFactor(root);

    if(balanceFactor > 1 && gatorID < root->left->gatorID){
        return rotateRight(root);
    }
    else if(balanceFactor > 1 && gatorID > root->left->gatorID){
        root->left = rotateLeft(root->left);
        return rotateRight(root);
    }
    else if(balanceFactor < -1 && gatorID > root->right->gatorID){
        return rotateLeft(root);
    }
    else if(balanceFactor < -1 && gatorID < root->right->gatorID){
        root->right = rotateRight(root->right);
        return rotateLeft(root);
    }
    return root;
}

Node* remove(Node* root, long gatorID, bool& worked){
    if(root == nullptr){
        return nullptr;
    }
    else if(gatorID < root->gatorID){
        root->left = remove(root->left, gatorID, worked);
    }
    else if(gatorID > root->gatorID){
        root->right = remove(root->right, gatorID, worked);
    }
    else if(gatorID == root->gatorID) {
        worked = true;
        if (root->left != nullptr && root->right != nullptr) {
            Node* temp = getInorderSuccessor(root->right);
            root->gatorID = temp->gatorID;
            root->name = temp->name;
            root->right = remove(root->right, root->gatorID, worked);
        }
        else{
            if(root->left == nullptr){
                return root->right;
            }
            else if(root->right == nullptr){
                cout << "successful" << endl;
                return root->left;
            }
        }
    }
    root->height = max(getHeight(root->left),getHeight(root->right)) + 1;
    return root;
}

void searchId(Node* root, long gatorID){
    if(root == nullptr){
        cout << "unsuccessful" << endl;
    }
    else if(root->gatorID == gatorID){
        cout << root->name << endl;
    }
    else if(gatorID < root->gatorID){
        searchId(root->left, gatorID);
    }
    else if(gatorID > root->gatorID){
        searchId(root->right, gatorID);
    }
}

void searchName(Node* root, string name, bool& found){
    if(root == nullptr){
        return;
    }
    else if(root->name.compare(name) == 0){
        found = true;
        cout << root->gatorID << endl;
    }
    searchName(root->left, name, found);
    searchName(root->right, name, found);
}

void printInorder(Node* root, bool& first){
    if(root == nullptr){
        return;
    }
    printInorder(root->left, first);
    if(first){
        cout << root->name;
        first = false;
    }
    else {
        cout << ", " << root->name;
    }
    printInorder(root->right, first);
}

void printPreorder(Node* root, bool& first){
    if(root == nullptr){
        return;
    }
    if(first){
        cout << root->name;
        first = false;
    }
    else {
        cout << ", " << root->name;
    }
    printPreorder(root->left, first);
    printPreorder(root->right, first);
}

void printPostorder(Node* root, bool& first){
    if(root == nullptr){
        return;
    }
    printPostorder(root->left, first);
    printPostorder(root->right, first);
    if(first){
        cout << root->name;
        first = false;
    }
    else {
        cout << ", " << root->name;
    }
}

int printLevelCount(Node* root){
    if(root == nullptr){
        return 0;
    }
    else {
        int left = printLevelCount(root->left);
        int right = printLevelCount(root->right);
        if (left > right)
            return(left + 1);
        else
            return(right + 1);
    }
}

void removeInorderN(Node* root, Node*& saveRoot, int index, int& count, bool& worked){
    if(root == nullptr){
        return;
    }
    removeInorderN(root->left, saveRoot, index, count, worked);
    if(count == index && !worked) {
        saveRoot = remove(saveRoot, root->gatorID, worked);
    }
    count++;
    removeInorderN(root->right, saveRoot, index, count, worked);
}

int main() {
    Node* root = nullptr;
    bool worked = false;
    bool first = true;
    int count = 0;
    int numCommands;
    cin >> numCommands;
    while(numCommands != -1){
        string command;
        getline(cin, command);
        if(command.substr(0, 6).compare("insert") == 0){
            int pos = command.substr(8).find('"');
            string name = command.substr(8, pos);
            string ID = command.substr((10 + pos));
            if(checkName(name) && checkID(ID)){
                long gatorID = stol(ID);
                root = insert(root, gatorID, name);
            }
            else{
                cout << "unsuccessful" << endl;
            }
        }
        else if(command.substr(0, 13).compare("removeInorder") == 0){
            int index = stoi(command.substr(14));
            removeInorderN(root, root, index, count, worked);
            if(!worked){
                cout << "unsuccessful" << endl;
                count = 0;
            }
            else{
                cout << "successful" << endl;
                count = 0;
                worked = false;
            }
        }
        else if(command.substr(0, 6).compare("remove") == 0){
            string ID = command.substr(7);
            if(checkID(ID)){
                long gatorID = stol(ID);
                root = remove(root, gatorID, worked);
                if(!worked){
                    cout << "unsuccessful" << endl;
                }
                else{
                    cout << "successful" << endl;
                    worked = false;
                }
            }
            else{
                cout << "unsuccessful" << endl;
            }
        }
        else if(command.substr(0, 6).compare("search") == 0){
            if(command[7] == '"'){
                int pos = command.substr(8).find('"');
                string name = command.substr(8, pos);
                if(checkName(name)){
                    searchName(root, name, worked);
                    if(!worked){
                        cout << "unsuccessful" << endl;
                    }
                    else{
                        worked = false;
                    }
                }
                else{
                    cout << "unsuccessful" << endl;
                }
            }
            else{
                string ID = command.substr(7);
                if(checkID(ID)){
                    long gatorID = stol(ID);
                    searchId(root, gatorID);
                }
                else{
                    cout << "unsuccessful" << endl;
                }
            }
        }
        else if(command.compare("printInorder") == 0){
            printInorder(root, first);
            cout << endl;
            first = true;
        }
        else if(command.compare("printPreorder") == 0){
            printPreorder(root, first);
            cout << endl;
            first = true;
        }
        else if(command.compare("printPostorder") == 0){
            printPostorder(root, first);
            cout << endl;
            first = true;
        }
        else if(command.compare("printLevelCount") == 0){
            cout << printLevelCount(root) << endl;
        }
        numCommands--;
    }
    return 0;
}
