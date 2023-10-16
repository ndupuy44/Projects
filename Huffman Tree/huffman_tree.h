#include <iostream>
#include <unordered_map>
#include <vector>
#include <queue>
using namespace std;

class huffman_tree {
private:
    struct treeNode{
        char element;
        int frequency;
        treeNode* left;
        treeNode* right;
        treeNode(char el, int fr, treeNode* l, treeNode* r){
            element = el;
            frequency = fr;
            left = l;
            right = r;
        }
    };

    struct comp{
        bool operator()(const treeNode* l, const treeNode* r) const
        {
            return l->frequency > r->frequency;
        }
    };

    unordered_map<char, int> frequencyTable;
    unordered_map<char, string> codes;
    treeNode* root;
public:
    void makeCodes(treeNode* root, string code){
        if(root == nullptr){
            return;
        }
        if(root->left == nullptr && root->right == nullptr){
            if(code.size() == 0){
                codes[root->element] = "0";
            }
            else {
                codes[root->element] = code;
            }
        }
        makeCodes(root->left, code + "0");
        makeCodes(root->right, code + "1");
    }

    /*
    Preconditions: input is a string of characters with ascii values 0-127
    Postconditions: Reads the characters of input and constructs a
    huffman tree based on the character frequencies of the file contents
    */

    huffman_tree(const string& input) {
        for (char ch: input) {
            frequencyTable[ch]++;
        }

        priority_queue<treeNode*, vector<treeNode*>, comp> pq;
        for (auto p : frequencyTable) {
            treeNode* node = new treeNode(p.first, p.second, nullptr, nullptr);
            pq.push(node);
        }

        while(pq.size() != 1){
            treeNode* left = pq.top();
            pq.pop();
            treeNode* right = pq.top();
            pq.pop();

            int sum = left->frequency + right->frequency;
            treeNode* node = new treeNode('\0', sum, left, right);
            pq.push(node);
        }

        root = pq.top();
        makeCodes(root, "");
    }


    /*
    Preconditions: input is a character with ascii value between 0-127
    Postconditions: Returns the Huffman code for character if character is in the tree
    and an empty string otherwise.
    */

    string get_character_code(char character) const {
        if(codes.find(character) != codes.end()){
            return codes.at(character);
        }
        return "";
    }


    /*
    Preconditions: input is a string of characters with ascii values 0-127
    Postconditions: Returns the Huffman encoding for the contents of input
    If input contains letters not present in the huffman_tree,
    return an empty string
    */

    string encode(const string& input) const {
        string encoded = "";
        for(char ch : input){
            string str = get_character_code(ch);
            if(str.size() == 0){
                encoded = "";
                break;
            }
            else{
                encoded += str;
            }
        }
        return encoded;
    }


    /*
    Preconditions: string_to_decode is a string containing Huffman-encoded text
    Postconditions: Returns the plaintext represented by the string if the string
    is a valid Huffman encoding and an empty string otherwise
    */

    string decode(const string& string_to_decode) const {
        string decoded = "";
        treeNode* iterator = root;
        for(char ch : string_to_decode){
            if(ch == '0'){
                iterator = iterator->left;
            }
            else if(ch == '1'){
                iterator = iterator->right;
            }
            else{
                decoded = "";
                break;
            }
            if(iterator->left == nullptr && iterator->right == nullptr){
                decoded += iterator->element;
                iterator = root;
            }
        }
        return decoded;
    }
};
